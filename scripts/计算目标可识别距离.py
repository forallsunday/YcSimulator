# -*- coding: utf-8 -*-
# @Author: Chongyang Liu
# @Date:   2026-03-06 14:50:05
# @Last Modified by:   Chongyang Liu
# @Last Modified time: 2026-03-06 18:11:44
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
        'visible_range': 140.0,  # 可见光识别距离 (km)
        'infrared_range': 150.0,  # 红外识别距离 (km)
    },
    'transport_aircraft': {
        'size': np.array([50, 50, 15]),
        'visible_range': 120.0,
        'infrared_range': 140.0,
    },
    'missile_launcher': {
        'size': np.array([6, 3, 3]),
        'visible_range': 100.0,
        'infrared_range': 50.0,
    }
}

# 约翰逊准则：识别概率达到50%时，目标像元数不小于8
JOHNSON_CRITERION_PIXELS = 10


def calc_target_pixels(target_size, flight_height, photo_type, depression_angle, azimuth_angle):
    """
    计算目标最短边在探测器上占的像元数
    
    参数：
        target_size: 目标尺寸 [长, 宽, 高] (m)
        flight_height: 飞行高度 (m)
        photo_type: 照相类型
        depression_angle: 俯角 - 与竖直方向的夹角 (°)
        azimuth_angle: 位角 - 与北方向的夹角 (°)
    
    返回：
        min_pixels: 目标最短边所占像元数
    """
    # 将角度转换为弧度
    depression_rad = np.radians(depression_angle)

    # 计算斜距离
    # 俯角为与竖直方向的夹角
    # slant_distance = h / cos(depression_angle)
    slant_distance = flight_height / np.cos(depression_rad)

    # 焦距转换为米 (mm -> m)
    focal_length = focal_lengths[photo_type]  # m

    # 像元尺寸（标准为5μm）
    pixel_size = pixels_sizes[photo_type]  # m

    # 获取目标的最短边
    min_target_size = np.min(target_size[:2])  # 取长、宽中的较小值（忽略高）

    # 根据约翰逊准则计算像元数
    # 像元数 = 目标尺寸 × 焦距 / (斜距 × 像元尺寸)
    # min_pixels = min_target_size * focal_length / (slant_distance * pixel_size)
    min_pixels = min_target_size * focal_length / slant_distance / pixel_size

    return min_pixels


if __name__ == "__main__":
    flight_height = 17000  # 17km 飞行高度
    azimuth_angle = 45  # 位角

    print("=" * 60)
    print("不同俯角下的像元数变化")
    print("=" * 60)

    target = TARGETS['missile_launcher']

    print(f"飞行高度: {flight_height}m, 位角: {azimuth_angle}°\n")

    # 拍照类型
    # photo_type = '可见光小视场-长焦'
    photo_type = '红外小视场-长焦'
    # photo_type = '可见光大视场-短焦'
    # photo_type = '红外大视场-短焦'

    for depression_angle in [60, 70, 80, 83, 85]:
        # 计算该俯角下的斜距
        depression_rad = np.radians(depression_angle)
        slant_dist = flight_height / np.cos(depression_rad)
        pixels = calc_target_pixels(target['size'], flight_height, photo_type, depression_angle, azimuth_angle)
        print(f"俯角 {depression_angle}°, 斜距 {slant_dist/1000:3.1f}km: {pixels:8.2f} 像元")

    # !!! 可见光判断是否可以识别是 10个像素，红外判断是否可以识别是 4个像素
    # 因为50km时，3m物体, 红外小视场-长焦的像元数是4.48，所以取4个像素作为红外的识别标准
