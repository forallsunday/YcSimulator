/**
 * @Author: Chongyang Liu
 * @Date:   2023-04-10 14:41:56
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2023-04-10 15:08:47
 */

#include <rotation.h>

namespace rot {
Eigen::Matrix3d Rx(double rad) {
    Eigen::Matrix3d R;
    R << 1, 0, 0, 0, cos(rad), sin(rad), 0, -sin(rad), cos(rad);
    return R;
}

Eigen::Matrix3d Ry(double rad) {
    Eigen::Matrix3d R;
    R << cos(rad), 0, -sin(rad), 0, 1, 0, sin(rad), 0, cos(rad);
    return R;
}

Eigen::Matrix3d Rz(double rad) {
    Eigen::Matrix3d R;
    R << cos(rad), sin(rad), 0, -sin(rad), cos(rad), 0, 0, 0, 1;
    return R;
}

Eigen::Matrix3d calcRotationMatrix(double yaw, double pitch, double roll, bool isRad) {
    if (!isRad) {
        yaw = yaw * MY_PI / 180;
        pitch = pitch * MY_PI / 180;
        roll = roll * MY_PI / 180;
    }
    Eigen::Matrix3d R;
    R = Rx(roll) * Ry(pitch) * Rz(yaw);
    return R;
}

Eigen::Vector3d calcRotationVector(double yaw, double pitch, double roll, bool isRad) {
    Eigen::Matrix3d R = calcRotationMatrix(yaw, pitch, roll, isRad);
    Eigen::AngleAxisd angle_axis(R);
    return angle_axis.angle() * angle_axis.axis();
}

Eigen::Matrix3d calcRotationMatrix(double yaw_body, double pitch_body, double roll_body,
                                   double depression, double azimuth,
                                   bool isRad) {
    if (!isRad) {
        yaw_body = yaw_body * MY_PI / 180;
        pitch_body = pitch_body * MY_PI / 180;
        roll_body = roll_body * MY_PI / 180;
        depression = depression * MY_PI / 180;
        azimuth = azimuth * MY_PI / 180;
    }
    Eigen::Matrix3d R;
    R = Ry(azimuth) * Rx(depression) * Rx(roll_body) * Ry(pitch_body) * Rz(yaw_body);
    return R;
}

Eigen::Vector3d calcRotationVector(double yaw_body, double pitch_body, double roll_body,
                                   double depression, double azimuth,
                                   bool isRad) {
    Eigen::Matrix3d R = calcRotationMatrix(yaw_body, pitch_body, roll_body, depression, azimuth, isRad);
    Eigen::AngleAxisd angle_axis(R);
    return angle_axis.angle() * angle_axis.axis();
}

Eigen::Vector3d rmat2Euler(Eigen::Matrix3d R, bool isRad) {
    double yaw = atan2(R(0, 1), R(0, 0));
    double pitch = -asin(R(0, 2));
    double roll = atan2(R(1, 2), R(2, 2));
    if (!isRad) {
        yaw = yaw * 180 / MY_PI;
        pitch = pitch * 180 / MY_PI;
        roll = roll * 180 / MY_PI;
    }
    return Eigen::Vector3d(yaw, pitch, roll);
}

Eigen::Vector3d rvec2Euler(Eigen::Vector3d rvec, bool isRad) {
    // rvec to rmat
    Eigen::AngleAxisd angle_axis(rvec.norm(), rvec.normalized());
    Eigen::Matrix3d R = angle_axis.matrix();
    return rmat2Euler(R, isRad);
}

}  // namespace rot