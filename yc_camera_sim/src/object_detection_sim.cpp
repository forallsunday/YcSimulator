#include "object_detection_sim.h"
#include <algorithm>
#include <cmath>

ObjectDetectionSim::ObjectDetectionSim() {
    initDefaultTargets();
}

void ObjectDetectionSim::initDefaultTargets() {
    // 预置目标尺寸数据库
    // entity_type 值需根据实际 ICD 定义填写, 此处为示例值
    // 大型舰船 320×75×60 m
    target_db_[1] = {320.0, 75.0, 60.0};
    // 运输机 50×50×15 m
    target_db_[2] = {50.0, 50.0, 15.0};
    // 导弹发射车 6×3×3 m
    target_db_[3] = {6.0, 3.0, 3.0};
}

void ObjectDetectionSim::registerTarget(uint16_t entity_type, const TargetSizeInfo &size) {
    target_db_[entity_type] = size;
}

double ObjectDetectionSim::getFocalLength(OpticalType type) const {
    switch (type) {
    case OpticalType::EO_NARROW: return FOCAL_EO_NARROW;
    case OpticalType::EO_WIDE:   return FOCAL_EO_WIDE;
    case OpticalType::IR_NARROW: return FOCAL_IR_NARROW;
    case OpticalType::IR_WIDE:   return FOCAL_IR_WIDE;
    default:                     return FOCAL_EO_NARROW;
    }
}

double ObjectDetectionSim::getPixelSize(OpticalType type) const {
    switch (type) {
    case OpticalType::EO_NARROW: // fall through
    case OpticalType::EO_WIDE:   return PIXEL_SIZE_EO;
    case OpticalType::IR_NARROW: // fall through
    case OpticalType::IR_WIDE:   return PIXEL_SIZE_IR;
    default:                     return PIXEL_SIZE_EO;
    }
}

double ObjectDetectionSim::getJohnsonThreshold(OpticalType type) const {
    switch (type) {
    case OpticalType::EO_NARROW:
    case OpticalType::EO_WIDE:   return JOHNSON_THRESHOLD_EO;
    case OpticalType::IR_NARROW:
    case OpticalType::IR_WIDE:   return JOHNSON_THRESHOLD_IR;
    default:                     return JOHNSON_THRESHOLD_EO;
    }
}

double ObjectDetectionSim::calcAngleFromVertical(double dep_body_deg, double az_body_deg,
                                                  double pitch_deg, double roll_deg) const {
    // 角度转弧度
    const double dep   = dep_body_deg * DEG2RAD;
    const double az    = az_body_deg * DEG2RAD;
    const double pitch = pitch_deg * DEG2RAD;
    const double roll  = roll_deg * DEG2RAD;

    // 视轴在机体系下的单位方向向量 (x-前, y-右, z-下)
    // 俯角 dep: 与z-下的夹角, 0°=正下方, 90°=水平前方
    // 位角 az:  与x-前的夹角, 向右为正
    //   dep=0  → [0, 0, 1] (正下方)
    //   dep=90°, az=0° → [1, 0, 0] (正前方)
    //   dep=90°, az=90° → [0, 1, 0] (正右方)
    const double los_bx = std::sin(dep) * std::cos(az);
    const double los_by = std::sin(dep) * std::sin(az);
    const double los_bz = std::cos(dep);

    // 机体系 → NED 旋转矩阵 R = Rz(ψ) · Ry(θ) · Rx(φ)
    // NED 向下分量 (第3行) 与航向角 ψ 无关:
    //   ned_z = -sin(θ)·los_bx + cos(θ)·sin(φ)·los_by + cos(θ)·cos(φ)·los_bz
    const double cp = std::cos(pitch);
    const double sp = std::sin(pitch);
    const double cr = std::cos(roll);
    const double sr = std::sin(roll);

    const double ned_z = -sp * los_bx + cp * sr * los_by + cp * cr * los_bz;

    // ned_z > 0 表示视轴有向下分量, 可以看到地面
    if (ned_z <= 0.0) {
        return MY_PI / 2.0; // 视轴向上, 无法看到地面
    }

    // 视轴与竖直向下方向的夹角
    double cos_alpha = ned_z;
    if (cos_alpha > 1.0) cos_alpha = 1.0;

    return std::acos(cos_alpha);
}

double ObjectDetectionSim::calcMinProjectedSize(const TargetSizeInfo &target, double alpha) const {
    // 地面最短边 (不知道目标朝向, 取 min(L, W) 作为最保守估计)
    const double min_ground = std::min(target.length, target.width);
    const double H          = target.height;

    const double cos_a = std::cos(alpha);
    const double sin_a = std::sin(alpha);

    // 情况1: 最短地面边恰好在交叉航向方向 (无透视缩短)
    //   图像上最小尺寸 = min_ground
    // 情况2: 最短地面边在沿航向方向 (有透视缩短, 但可看到目标侧面高度)
    //   该方向的轮廓 = min_ground·cos(α) + H·sin(α)
    // 取最保守 (最小) 值
    const double along_range_size = min_ground * cos_a + H * sin_a;

    return std::min(min_ground, along_range_size);
}

double ObjectDetectionSim::calcTargetPixels(uint16_t entity_type, double flight_height,
                                             OpticalType optical_type,
                                             double dep_body_deg, double az_body_deg,
                                             double heading_deg, double pitch_deg,
                                             double roll_deg) const {
    // 查找目标尺寸
    auto it = target_db_.find(entity_type);
    if (it == target_db_.end()) {
        return -1.0; // 未知目标类型
    }

    const TargetSizeInfo &target = it->second;

    // 计算视轴在 NED 系下与竖直向下方向的夹角 (航向不影响此角)
    const double alpha = calcAngleFromVertical(dep_body_deg, az_body_deg, pitch_deg, roll_deg);

    // cos 过小时斜距趋于无穷
    const double cos_alpha = std::cos(alpha);
    if (cos_alpha < 1e-6) {
        return 0.0;
    }

    // 斜距 = 飞行高度 / cos(α)
    const double slant_distance = flight_height / cos_alpha;

    // 目标最小投影尺寸 (考虑透视效应)
    const double min_projected = calcMinProjectedSize(target, alpha);

    // 焦距和像元尺寸
    const double focal_length = getFocalLength(optical_type);
    const double pixel_size   = getPixelSize(optical_type);

    // 像元数 = 最小投影尺寸 × 焦距 / (斜距 × 像元尺寸)
    return min_projected * focal_length / slant_distance / pixel_size;
}

bool ObjectDetectionSim::canDetect(uint16_t entity_type, double flight_height,
                                      OpticalType optical_type,
                                      double dep_body_deg, double az_body_deg,
                                      double heading_deg, double pitch_deg,
                                      double roll_deg, double image_scale) const {
    const double pixels = calcTargetPixels(entity_type, flight_height, optical_type,
                                            dep_body_deg, az_body_deg,
                                            heading_deg, pitch_deg, roll_deg);
    if (pixels < 0.0) {
        return false; // 未知目标类型
    }

    // 有效像元数 = 传感器像元数 / 图像缩放因子
    // 例如: EO 5120×4096 缩放到 1280×1024 时, image_scale=4.0
    const double effective_pixels = pixels / image_scale;

    return effective_pixels >= getJohnsonThreshold(optical_type);
}
