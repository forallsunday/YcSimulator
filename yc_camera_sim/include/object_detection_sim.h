#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <map>

/**
 * @brief 光学类型枚举
 */
enum class OpticalType : uint8_t {
    EO_NARROW = 0, // 可见光小视场-长焦
    EO_WIDE   = 1, // 可见光大视场-短焦
    IR_NARROW = 2, // 红外小视场-长焦
    IR_WIDE   = 3, // 红外大视场-短焦
};

/**
 * @brief 目标尺寸信息 [长, 宽, 高] (m)
 */
struct TargetSizeInfo {
    double length; // 长 (m)
    double width;  // 宽 (m)
    double height; // 高 (m)
};

/**
 * @brief 目标探测模拟类
 *
 * 基于约翰逊准则，根据目标在探测器中所占像元数判断目标是否可被识别。
 * - 可见光识别标准: 目标最小投影尺寸所占像元数 >= 10
 * - 红外识别标准:   目标最小投影尺寸所占像元数 >= 4
 *
 * 坐标约定:
 * - 机体系: x-前, y-右, z-下 (前右下)
 * - 俯角 (depression): 相机视轴与载机向下方向(z轴)的夹角, 0°=正下方, 90°=水平
 * - 位角 (azimuth):     相机视轴在水平面的投影与机头方向(x轴)的夹角, 向右为正
 * - 载机姿态: 航向角(ψ), 俯仰角(θ, 抬头正), 横滚角(φ, 右滚正), ZYX欧拉角
 *
 * 计算流程:
 * 1. 由俯角和位角构造机体系下视轴方向向量
 * 2. 经 R(ψ,θ,φ) 旋转到NED系, 取向下分量计算视轴与竖直方向夹角 α
 * 3. 斜距 = 飞行高度 / cos(α)
 * 4. 考虑投影效应, 计算目标最小投影尺寸
 * 5. 像元数 = 最小投影尺寸 × 焦距 / (斜距 × 像元尺寸)
 */
class ObjectDetectionSim {
  public:
    ObjectDetectionSim();
    ~ObjectDetectionSim() = default;

    /**
     * @brief 判断目标是否可识别
     *
     * @param entity_type   目标实体类型 (U2_EntityType)
     * @param flight_height 飞行高度 (m)
     * @param optical_type  光学类型 (可见光/红外, 大/小视场)
     * @param dep_body_deg  相机俯角 - 与载机向下方向的夹角 (deg), [0, 90], 0=正下方
     * @param az_body_deg   相机位角 - 与载机机头方向的夹角 (deg), [-180, 180], 向右为正
     * @param heading_deg   载机航向角 (deg)
     * @param pitch_deg     载机俯仰角 (deg), 抬头为正
     * @param roll_deg      载机横滚角 (deg), 右滚为正
     * @param image_scale    图像缩放因子 (默认1.0, 无缩放)
     *                       当可见光(5120×4096)缩放至1280×1024输出时, 传入4.0
     *                       有效像元数 = 传感器像元数 / image_scale
     * @return true  目标可被识别
     * @return false 目标不可识别（像元数不足或未知目标类型）
     */
    bool canDetect(uint16_t entity_type, double flight_height, OpticalType optical_type,
                   double dep_body_deg, double az_body_deg,
                   double heading_deg = 0.0, double pitch_deg = 0.0,
                   double roll_deg = 0.0, double image_scale = 1.0) const;

    /**
     * @brief 计算目标最小投影尺寸在探测器上所占的像元数
     *
     * @param entity_type   目标实体类型 (U2_EntityType)
     * @param flight_height 飞行高度 (m)
     * @param optical_type  光学类型
     * @param dep_body_deg  相机俯角 (deg), [0, 90]
     * @param az_body_deg   相机位角 (deg), [-180, 180]
     * @param heading_deg   载机航向角 (deg)
     * @param pitch_deg     载机俯仰角 (deg)
     * @param roll_deg      载机横滚角 (deg)
     * @return double 像元数, 返回 -1 表示目标类型未知
     */
    double calcTargetPixels(uint16_t entity_type, double flight_height, OpticalType optical_type,
                            double dep_body_deg, double az_body_deg,
                            double heading_deg = 0.0, double pitch_deg = 0.0,
                            double roll_deg = 0.0) const;

    /**
     * @brief 注册/更新目标尺寸信息
     * @param entity_type 目标实体类型
     * @param size        目标尺寸 [长, 宽, 高] (m)
     */
    void registerTarget(uint16_t entity_type, const TargetSizeInfo &size);

  private:
    static constexpr double MY_PI   = 3.14159265358979323846;
    static constexpr double DEG2RAD = MY_PI / 180.0;

    // 约翰逊准则阈值
    static constexpr double JOHNSON_THRESHOLD_EO = 10.0; // 可见光识别阈值 (像元)
    static constexpr double JOHNSON_THRESHOLD_IR = 4.0;  // 红外识别阈值 (像元)

    // 焦距 (m)
    static constexpr double FOCAL_EO_NARROW = 1960e-3; // 可见光小视场-长焦
    static constexpr double FOCAL_EO_WIDE   = 392e-3;  // 可见光大视场-短焦
    static constexpr double FOCAL_IR_NARROW = 1120e-3; // 红外小视场-长焦
    static constexpr double FOCAL_IR_WIDE   = 224e-3;  // 红外大视场-短焦

    // 像元尺寸 (m)
    static constexpr double PIXEL_SIZE_EO = 4.5e-6; // 可见光像元尺寸
    static constexpr double PIXEL_SIZE_IR = 15e-6;  // 红外像元尺寸

    // 目标尺寸数据库: entity_type -> TargetSizeInfo
    std::map<uint16_t, TargetSizeInfo> target_db_;

    double getFocalLength(OpticalType type) const;
    double getPixelSize(OpticalType type) const;
    double getJohnsonThreshold(OpticalType type) const;

    /**
     * @brief 计算视轴在 NED 系下与竖直向下方向的夹角
     *
     * 机体系 LOS 方向:
     *   LOS_body = [sin(dep)*cos(az), sin(dep)*sin(az), cos(dep)]
     *   dep=0 → 正下方 [0,0,1], dep=90°,az=0 → 正前方 [1,0,0]
     *
     * 经 ZYX 欧拉角旋转 R(ψ,θ,φ) 到 NED 系, NED 向下分量:
     *   ned_z = -sinθ·los_bx + cosθ·sinφ·los_by + cosθ·cosφ·los_bz
     *   (航向角 ψ 不影响向下分量)
     *
     * @return 视轴与竖直向下方向的夹角 α (rad), [0, π/2]
     */
    double calcAngleFromVertical(double dep_body_deg, double az_body_deg,
                                 double pitch_deg, double roll_deg) const;

    /**
     * @brief 计算目标最小投影尺寸 (考虑透视效应)
     *
     * 视轴与竖直方向夹角为 α 时:
     * - 交叉航向的地面尺寸无透视缩短
     * - 沿航向的地面尺寸缩短为 d·cos(α)
     * - 目标高度 H 投影为 H·sin(α)
     *
     * 最保守的最小投影尺寸:
     *   min(min(L,W), min(L,W)·cos(α) + H·sin(α))
     *
     * @param target  目标尺寸
     * @param alpha   视轴与竖直向下方向夹角 (rad)
     * @return double 最小投影尺寸 (m)
     */
    double calcMinProjectedSize(const TargetSizeInfo &target, double alpha) const;

    void initDefaultTargets();
};
