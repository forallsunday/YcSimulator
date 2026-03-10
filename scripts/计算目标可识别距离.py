# -*- coding: utf-8 -*-
# @Author: Chongyang Liu
# @Date:   2026-03-06 14:50:05
# @Last Modified by:   Chongyang Liu
# @Last Modified time: 2026-03-10 21:27:53
''' 
根据约翰逊准则,利用目标在探测器中所占像元数计算目标的探测识别概率,一般情况下,识别概率达到50%时,要求目标所成像元数不小于8。
指标要求：
大型舰船（320*75*60） 可见光目标背景对比度4:1， 识别距离140km
运输机（50*50*15） 可见光目标背景对比度4:1， 识别距离120km
导弹发射车（6*3*3） 可见光目标背景对比度8:1， 识别距离100km
大型舰船（320*75*60） 红外目标背景温差5度， 识别距离150km
运输机（50*50*15） 红外目标背景温差5度， 识别距离140km
导弹发射车（6*3*3） 红外目标背景温差5度， 识别距离50km

可见光小视场-长焦         1960.0f
可见光大视场-短焦         392.0f 
红外小视场-长焦           500.0f 
红外大视场-短焦           125.0f 

坐标约定:
- 机体系: x-前, y-右, z-下 (前右下)
- 俯角 (depression): 相机视轴与载机向下方向(z轴)的夹角, 0°=正下方, 90°=水平
- 位角 (azimuth):     相机视轴在水平面的投影与机头方向(x轴)的夹角, 向右为正
- 载机姿态: 航向角(ψ), 俯仰角(θ, 抬头正), 横滚角(φ, 右滚正), ZYX欧拉角

'''

from math import pi
import numpy as np

# 焦距定义（mm）
focal_lengths = {
    '可见光小视场-长焦': 1960e-3,  # 可见光小视场-长焦
    '可见光大视场-短焦': 392e-3,  # 可见光大视场-短焦
    '红外小视场-长焦': 1120e-3,  # 红外小视场-长焦
    '红外大视场-短焦': 224e-3  # 红外大视场-短焦
}

pixels_sizes = {
    '可见光小视场-长焦': 4.5e-6,  # 可见光小视场-长焦
    '可见光大视场-短焦': 4.5e-6,  # 可见光大视场-短焦
    '红外小视场-长焦': 15e-6,  # 红外小视场-长焦
    '红外大视场-短焦': 15e-6  # 红外大视场-短焦
}

# 目标定义
TARGETS = {
    'large_ship': {
        'size': np.array([320, 75, 60]),  # 尺寸 (长, 宽, 高)
        'EO_range': 140.0,  # 可见光识别距离 (km)
        'IR_range': 150.0,  # 红外识别距离 (km)
    },
    'transport_aircraft': {
        'size': np.array([50, 50, 15]),
        'EO_range': 120.0,
        'IR_range': 140.0,
    },
    'missile_launcher': {
        'size': np.array([6, 3, 3]),
        'EO_range': 100.0,
        'IR_range': 50.0,
    }
}

# 约翰逊准则：识别概率达到50%时，目标像元数不小于8
JOHNSON_CRITERION_PIXELS = 10


def calc_angle_from_vertical(dep_body_deg, az_body_deg, pitch_deg=0.0, roll_deg=0.0):
    """
    将机体系下的视轴指向通过载机姿态旋转到大地系(NED)，
    计算视轴与竖直向下方向的夹角。

    相机角度定义 (机体系 x-前, y-右, z-下):
        dep_body_deg: 俯角 - 视轴与载机向下方向(z轴)的夹角 (deg)
                      0° = 正下方, 90° = 水平
        az_body_deg:  位角 - 视轴水平投影与机头方向(x轴)的夹角 (deg)
                      向右为正

    载机姿态:
        pitch_deg: 俯仰角 (deg), 抬头为正
        roll_deg:  横滚角 (deg), 右滚为正
        (航向角不影响与竖直方向的夹角, 故不需要)

    LOS_body = [sin(dep)*cos(az), sin(dep)*sin(az), cos(dep)]
      dep=0  → [0,0,1] 正下方
      dep=90°,az=0° → [1,0,0] 正前方

    ZYX欧拉角旋转矩阵 R = Rz(ψ)·Ry(θ)·Rx(φ) 的第3行(NED向下分量):
      ned_z = -sinθ·los_bx + cosθ·sinφ·los_by + cosθ·cosφ·los_bz
      (与航向角 ψ 无关)

    返回：
        alpha_rad: 视轴与竖直向下方向的夹角 (rad), [0, π/2]
    """
    dep = np.radians(dep_body_deg)
    az = np.radians(az_body_deg)
    pitch = np.radians(pitch_deg)
    roll = np.radians(roll_deg)

    # 视轴在机体系下的单位方向向量
    los_bx = np.sin(dep) * np.cos(az)
    los_by = np.sin(dep) * np.sin(az)
    los_bz = np.cos(dep)

    # NED 向下分量
    cp, sp = np.cos(pitch), np.sin(pitch)
    cr, sr = np.cos(roll), np.sin(roll)
    ned_z = -sp * los_bx + cp * sr * los_by + cp * cr * los_bz

    if ned_z <= 0:
        return np.pi / 2.0  # 视轴向上, 无法看到地面

    cos_alpha = np.clip(ned_z, -1.0, 1.0)
    return np.arccos(cos_alpha)


def calc_min_projected_size(target_size, alpha_rad):
    """
    计算目标最小投影尺寸 (考虑透视效应)

    视轴与竖直方向夹角为 α 时:
    - 交叉航向的地面尺寸: 无透视缩短
    - 沿航向的地面尺寸: 缩短为 d·cos(α)
    - 目标高度 H: 投影为 H·sin(α)

    不知道目标朝向, 取最保守估计:
    min_projected = min(min(L,W), min(L,W)·cos(α) + H·sin(α))

    参数：
        target_size: 目标尺寸 [长, 宽, 高] (m)
        alpha_rad:   视轴与竖直向下方向的夹角 (rad)
    返回：
        最小投影尺寸 (m)
    """
    min_ground = np.min(target_size[:2])  # min(L, W)
    H = target_size[2]

    cos_a = np.cos(alpha_rad)
    sin_a = np.sin(alpha_rad)

    # 情况1: 最短地面边在交叉航向 → 无缩短 = min_ground
    # 情况2: 最短地面边在沿航向 → min_ground·cos(α) + H·sin(α)
    along_range_size = min_ground * cos_a + H * sin_a

    return min(min_ground, along_range_size)


def calc_target_pixels(target_size, flight_height, photo_type, dep_body_deg, az_body_deg, pitch_deg=0.0, roll_deg=0.0):
    """
    计算目标最小投影尺寸在探测器上占的像元数

    参数：
        target_size:   目标尺寸 [长, 宽, 高] (m)
        flight_height: 飞行高度 (m)
        photo_type:    照相类型
        dep_body_deg:  相机俯角 - 与载机向下方向的夹角 (deg), [0,90], 0=正下方
        az_body_deg:   相机位角 - 与载机机头方向的夹角 (deg), 向右为正
        pitch_deg:     载机俯仰角 (deg), 抬头为正, 默认0
        roll_deg:      载机横滚角 (deg), 右滚为正, 默认0

    返回：
        min_pixels: 目标最小投影尺寸所占像元数
    """
    # 1. 计算视轴在NED系下与竖直方向的夹角 α
    alpha_rad = calc_angle_from_vertical(dep_body_deg, az_body_deg, pitch_deg, roll_deg)

    # 2. 斜距 = h / cos(α)
    cos_alpha = np.cos(alpha_rad)
    if cos_alpha < 1e-6:
        return 0.0
    slant_distance = flight_height / cos_alpha

    # 3. 目标最小投影尺寸 (考虑透视效应)
    min_projected = calc_min_projected_size(target_size, alpha_rad)

    # 4. 像元数 = 最小投影尺寸 × 焦距 / (斜距 × 像元尺寸)
    focal_length = focal_lengths[photo_type]
    pixel_size = pixels_sizes[photo_type]
    min_pixels = min_projected * focal_length / slant_distance / pixel_size

    return min_pixels


if __name__ == "__main__":
    flight_height = 17000  # 17km 飞行高度
    az_body_deg = 45  # 位角: 与机头方向的夹角 (deg)
    pitch_deg = 1.0  # 载机俯仰角 (deg)
    roll_deg = -2.0  # 载机横滚角 (deg)

    print("=" * 80)
    print("不同俯角下的像元数变化 (考虑载机姿态 + 目标投影效应)")
    print("=" * 80)

    target = TARGETS['missile_launcher']
    # target = TARGETS['transport_aircraft']

    print(f"飞行高度: {flight_height}m, 载机俯仰: {pitch_deg}°, 横滚: {roll_deg}°")
    print(f"目标尺寸: {target['size']}m\n")

    # 拍照类型
    # photo_type = '可见光小视场-长焦'
    photo_type = '红外小视场-长焦'
    # photo_type = '可见光大视场-短焦'
    # photo_type = '红外大视场-短焦'

    # 俯角: 与载机向下方向的夹角, 0°=正下方, 90°=水平
    for dep_body_deg in [0, 30, 60, 70, 80, 83, 85]:
        alpha_rad = calc_angle_from_vertical(dep_body_deg, az_body_deg, pitch_deg, roll_deg)
        alpha_deg = np.degrees(alpha_rad)
        cos_a = np.cos(alpha_rad)
        slant_dist = flight_height / cos_a if cos_a > 1e-6 else float('inf')
        min_proj = calc_min_projected_size(target['size'], alpha_rad)
        pixels = calc_target_pixels(target['size'], flight_height, photo_type, dep_body_deg, az_body_deg, pitch_deg,
                                    roll_deg)
        print(f"俯角 {dep_body_deg:2d}° (对地夹角 {alpha_deg:5.1f}°), "
              f"斜距 {slant_dist/1000:6.1f}km, "
              f"最小投影 {min_proj:6.1f}m: {pixels:8.2f} 像元")

    # !!! 可见光判断是否可以识别是 10个像素，红外判断是否可以识别是 4个像素
    # 因为50km时，3m物体, 红外小视场-长焦的像元数是4.48，所以取4个像素作为红外的识别标准
