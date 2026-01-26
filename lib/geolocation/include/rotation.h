/**
 * @Author: Chongyang Liu
 * @Date:   2023-02-03 11:36:01
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2023-04-10 14:58:19
 */
/*
    Eigen 的旋转矩阵是旋转目标，不是旋转坐标系。故自己定义。
*/
#ifndef ROTATION_H
#define ROTATION_H

#define MY_PI 3.14159265358979323846  // pi

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace rot {
Eigen::Matrix3d Rx(double rad);

Eigen::Matrix3d Ry(double rad);

Eigen::Matrix3d Rz(double rad);

/// @brief 计算旋转矩阵(无框架角)
/// @param yaw      航向角
/// @param pitch    俯仰角
/// @param roll     横滚角
/// @param isRad    是否为弧度制
/// @return         旋转矩阵
Eigen::Matrix3d calcRotationMatrix(double yaw, double pitch, double roll, bool isRad = true);

/// @brief 计算旋转向量(无框架角)
/// @param yaw      航向角
/// @param pitch    俯仰角
/// @param roll     横滚角
/// @param isRad    是否为弧度制
/// @return         旋转向量
Eigen::Vector3d calcRotationVector(double yaw, double pitch, double roll, bool isRad = true);

/// @brief 计算航空相机的旋转矩阵
/// @param yaw_body     载机的航向角
/// @param pitch_body   载机的俯仰角
/// @param roll_body    载机的横滚角
/// @param depression   相机的俯仰角
/// @param azimuth      相机的方位角
/// @param isRad        是否为弧度制 
/// @return             旋转矩阵
Eigen::Matrix3d calcRotationMatrix(double yaw_body, double pitch_body, double roll_body,
                                   double depression, double azimuth,
                                   bool isRad = true);

/// @brief 计算航空相机的旋转向量
/// @param yaw_body     载机的航向角
/// @param pitch_body   载机的俯仰角
/// @param roll_body    载机的横滚角
/// @param depression   相机的俯仰角
/// @param azimuth      相机的方位角
/// @param isRad        是否为弧度制
/// @return             旋转向量
Eigen::Vector3d calcRotationVector(double yaw_body, double pitch_body, double roll_body,
                                   double depression, double azimuth,
                                   bool isRad = true);

Eigen::Vector3d rmat2Euler(Eigen::Matrix3d R, bool isRad = true);

Eigen::Vector3d rvec2Euler(Eigen::Vector3d rvec, bool isRad = true);
}  // namespace rot

#endif
