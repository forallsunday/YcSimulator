/**
 * @Author: Chongyang Liu
 * @Date:   2023-02-03 14:04:52
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-04-18 16:03:27
 */

#ifndef GEOLOCALIZATION_HPP
#define GEOLOCALIZATION_HPP

#include <Eigen/Core>

/**
 * @brief 基于视距(Line of Sight)的地理定位
 *
 * 该类用于实现基于视距的地理定位算法,通过计算目标与观测点之间的视线关系
 * 来确定目标的地理位置。
 */
class GeolocatorLOS
{
   public:
    GeolocatorLOS() {}
    GeolocatorLOS(Eigen::Vector3d body_lla, Eigen::Vector4d cam_ins, Eigen::Vector3d rvec);
    GeolocatorLOS(Eigen::Vector3d body_lla, Eigen::Matrix3d K, Eigen::Matrix3d R);
    GeolocatorLOS(Eigen::Vector3d body_lla, double fx, double fy, double cx, double cy,
                  Eigen::Vector3d rvec);

    Eigen::Vector3d get_target_ecef(const Eigen::Vector2d& pp, const double alt_obj);

    Eigen::Vector3d get_target_lla(const Eigen::Vector2d& pp, const double alt_obj);

   public:
    // initial parameters
    Eigen::Vector3d body_lla;  // 载机纬度经度高度
    Eigen::Vector4d cam_ins;   // 相机内参
    Eigen::Vector3d rvec;      // 相机旋转向量
    // altertive params
    Eigen::Matrix3d K, R;  // 相机内参矩阵和旋转矩阵
    // calculated params
    Eigen::Vector3d body_ecef;  // 载机ECEF坐标
};
#endif  // GEOLOCALIZATION_HPP
