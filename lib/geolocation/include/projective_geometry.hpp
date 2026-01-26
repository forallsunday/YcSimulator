/**
 * @Author: Chongyang Liu
 * @Date:   2023-02-10 14:35:59
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-05-18 14:31:28
 */
#ifndef COORDINATE_TRANSFORM_HPP
#define COORDINATE_TRANSFORM_HPP

#include <wgs84.h>

#include <Eigen/Core>

using namespace Eigen;

// template <typename Type, int Size>
// using Vector = Matrix<Type, Size, 1>;

#define MY_PI 3.14159265358979323846  // pi

template <typename T>
inline T DotProduct(const T x[3], const T y[3]) {
    return (x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
}

template <typename T>
inline void AngleAxisRotatePoint(const T angle_axis[3],
                                 const T pt[3],
                                 T result[3]) {
    const T theta2 = DotProduct(angle_axis, angle_axis);
    if (theta2 > T(std::numeric_limits<double>::epsilon())) {
        // Away from zero, use the rodriguez formula
        //
        //   result = pt costheta +
        //            (w x pt) * sintheta +
        //            w (w . pt) (1 - costheta)
        //
        // We want to be careful to only evaluate the square root if the
        // norm of the angle_axis vector is greater than zero. Otherwise
        // we get a division by zero.
        //
        const T theta = sqrt(theta2);
        const T costheta = cos(theta);
        const T sintheta = sin(theta);
        const T theta_inverse = T(1.0) / theta;

        const T w[3] = {angle_axis[0] * theta_inverse,
                        angle_axis[1] * theta_inverse,
                        angle_axis[2] * theta_inverse};

        // Explicitly inlined evaluation of the cross product for
        // performance reasons.
        const T w_cross_pt[3] = {w[1] * pt[2] - w[2] * pt[1],
                                 w[2] * pt[0] - w[0] * pt[2],
                                 w[0] * pt[1] - w[1] * pt[0]};
        const T tmp =
            (w[0] * pt[0] + w[1] * pt[1] + w[2] * pt[2]) * (T(1.0) - costheta);

        result[0] = pt[0] * costheta + w_cross_pt[0] * sintheta + w[0] * tmp;
        result[1] = pt[1] * costheta + w_cross_pt[1] * sintheta + w[1] * tmp;
        result[2] = pt[2] * costheta + w_cross_pt[2] * sintheta + w[2] * tmp;
    } else {
        // Near zero, the first order Taylor approximation of the rotation
        // matrix R corresponding to a vector w and angle theta is
        //
        //   R = I + hat(w) * sin(theta)
        //
        // But sintheta ~ theta and theta * w = angle_axis, which gives us
        //
        //  R = I + hat(angle_axis)
        //
        // and actually performing multiplication with the point pt, gives us
        // R * pt = pt + angle_axis x pt.
        //
        // Switching to the Taylor expansion near zero provides meaningful
        // derivatives when evaluated using Jets.
        //
        // Explicitly inlined evaluation of the cross product for
        // performance reasons.
        const T w_cross_pt[3] = {angle_axis[1] * pt[2] - angle_axis[2] * pt[1],
                                 angle_axis[2] * pt[0] - angle_axis[0] * pt[2],
                                 angle_axis[0] * pt[1] - angle_axis[1] * pt[0]};

        result[0] = pt[0] + w_cross_pt[0];
        result[1] = pt[1] + w_cross_pt[1];
        result[2] = pt[2] + w_cross_pt[2];
    }
}

// Note: Eigen version-----------------------------------------------------------------

template <typename T>
Vector<T, 3> ned2ecef(const Vector<T, 3>& ned, const Vector<T, 3>& lla_ecef) {
    T lat_ref = lla_ecef[0] * MY_PI / 180.;
    T lon_ref = lla_ecef[1] * MY_PI / 180.;
    T alt_ref = lla_ecef[2];

    Matrix<T, 3, 3> C;
    C(0, 0) = -sin(lat_ref) * cos(lon_ref);
    C(0, 1) = -sin(lat_ref) * sin(lon_ref);
    C(0, 2) = cos(lat_ref);
    C(1, 0) = -sin(lon_ref);
    C(1, 1) = cos(lon_ref);
    C(1, 2) = T(0);
    C(2, 0) = -cos(lat_ref) * cos(lon_ref);
    C(2, 1) = -cos(lat_ref) * sin(lon_ref);
    C(2, 2) = -sin(lat_ref);

    Vector<T, 3> ecef = C.transpose() * ned;

    return ecef;
}

template <typename T>
Vector<T, 3> ecef2lla(const Vector<T, 3>& ecef) {
    const T &x = ecef[0], &y = ecef[1], &z = ecef[2];
    T lon = atan2(y, x);
    T p = sqrt(x * x + y * y);
    T lat = atan2(z, p * (1 - WGS84__ecc_sqrd));
    T err = T(1.);
    T alt = T(0.);
    T Rew;
    while (abs(err) > 1e-10) {
        Rew = T(WGS84_a) / sqrt(T(1.) - WGS84__ecc_sqrd * sin(lat) * sin(lat));
        // Rns = WGS84_a / sqrt(T(1) - WGS84__ecc_sqrd * sin(lat) * sin(lat)) * (T(1) - WGS84__ecc_sqrd);
        if (abs(MY_PI / 2. - abs(lat)) > T(1e-3)) {
            alt = p / cos(lat) - Rew;
        } else {
            alt = ecef[2] / sin(lat) - (T(1.) - WGS84__ecc_sqrd) * Rew;
        }

        err = atan2(ecef[2] + WGS84__ecc_sqrd * Rew * sin(lat), p) - lat;
        lat = lat + err;
    }
    Vector<T, 3> lla(lat * 180. / MY_PI, lon * 180. / MY_PI, alt);

    return lla;
}
template <typename T>
Vector<T, 3> lla2ecef(const Vector<T, 3>& lla) {
    T lat = lla[0] * MY_PI / 180.;
    T lon = lla[1] * MY_PI / 180.;
    T alt = lla[2];

    T N = WGS84_a / sqrt(T(1) - WGS84__ecc_sqrd * sin(lat) * sin(lat));

    Vector<T, 3> ecef;
    ecef[0] = (N + alt) * cos(lat) * cos(lon);
    ecef[1] = (N + alt) * cos(lat) * sin(lon);
    ecef[2] = (N * (T(1) - WGS84__ecc_sqrd) + alt) * sin(lat);
    return ecef;
}
template <typename T>
Vector<T, 3> ecef2ned(const Vector<T, 3>& ecef, const Vector<T, 3>& lla_ref) {
    Matrix<T, 3, 3> C;
    T lat_ref = lla_ref[0] * MY_PI / 180.;
    T lon_ref = lla_ref[1] * MY_PI / 180.;
    T alt_ref = lla_ref[2];
    C(0, 0) = -sin(lat_ref) * cos(lon_ref);
    C(0, 1) = -sin(lat_ref) * sin(lon_ref);
    C(0, 2) = cos(lat_ref);
    C(1, 0) = -sin(lon_ref);
    C(1, 1) = cos(lon_ref);
    C(1, 2) = T(0);
    C(2, 0) = -cos(lat_ref) * cos(lon_ref);
    C(2, 1) = -cos(lat_ref) * sin(lon_ref);
    C(2, 2) = -sin(lat_ref);

    Vector<T, 3> ned;
    ned = C * ecef;

    return ned;
}
template <typename T>
Vector<T, 3> pixel2camera(const Vector<T, 2>& pixel, const Vector<T, 4>& cam_ins) {
    const T &fx = cam_ins[0], &fy = cam_ins[1], &cx = cam_ins[2], &cy = cam_ins[3];

    Vector<T, 3> pcam;
    pcam[0] = (pixel[0] - cx) / fx;
    pcam[1] = (pixel[1] - cy) / fy;
    pcam[2] = T(1);
    return pcam;
}

template <typename T>
Vector<T, 3> camera2ned(const Vector<T, 3>& pcam, const Vector<T, 3>& rvec, T scale = T(1)) {
    Vector<T, 3> pned;
    T rvec1_inv[3] = {-rvec[0], -rvec[1], -rvec[2]};
    AngleAxisRotatePoint(rvec1_inv, pcam.data(), pned.data());

    pned[0] = pned[0] / pned[2] * scale;
    pned[1] = pned[1] / pned[2] * scale;
    pned[2] = scale;
    return pned;
}

template <typename T>
Vector<T, 3> pixel2ned(const Vector<T, 2>& pixel, const Vector<T, 4>& cam_ins, const Vector<T, 3>& rvec, T scale = T(1)) {
    Vector<T, 3> pcam = pixel2camera(pixel, cam_ins);
    Vector<T, 3> pned = camera2ned(pcam, rvec, scale);
    return pned;
}
template <typename T>
Vector<T, 3> ned2camera(const Vector<T, 3>& pned, const Vector<T, 3>& rvec) {
    Vector<T, 3> pcam;
    AngleAxisRotatePoint(rvec.data(), pned.data(), pcam.data());
    return pcam;
}
template <typename T>
Vector<T, 2> camera2pixel(const Vector<T, 3>& pcam, const Vector<T, 4>& cam_ins) {
    const T &fx = cam_ins[0], &fy = cam_ins[1], &cx = cam_ins[2], &cy = cam_ins[3];
    Vector<T, 2> pixel;
    pixel[0] = pcam[0] / pcam[2] * fx + cx;
    pixel[1] = pcam[1] / pcam[2] * fy + cy;
    return pixel;
}
template <typename T>
Vector<T, 2> ned2pixel(
    const Vector<T, 3>& pned, const Vector<T, 3>& rvec, const Vector<T, 4>& cam_ins) {
    Vector<T, 3> pcam = ned2camera(pned, rvec);
    Vector<T, 2> pixel = camera2pixel(pcam, cam_ins);
    return pixel;
}

/// @brief 计算从图像上一点发出的射线的方向
/// @param pixel        图像上的点
/// @param cam_ins      相机内参
/// @param rvec         相机旋转向量
/// @param body_lla     相机所在位置的经纬度
/// @param body_ecef    相机所在位置的ECEF坐标
/// @return             射线方向
template <typename T>
Vector<T, 3> ray_direction(const Vector<T, 2>& pixel, const Vector<T, 4>& cam_ins, const Vector<T, 3>& rvec,
                           const Vector<T, 3>& body_lla, const Vector<T, 3>& body_ecef) {
    Vector<T, 3> p_ned = pixel2ned(pixel, cam_ins, rvec, T(body_lla[2]));
    Vector<T, 3> p_ecef = ned2ecef(p_ned, body_lla);
    p_ecef += body_ecef;
    Vector<T, 3> direction = p_ecef - body_ecef;
    direction.normalize();
    return direction;
}

/// @brief 将空间中一点投影到图像上
/// @param p_ecef       空间中的点 ECEF坐标系
/// @param body_ecef    相机所在位置 ECEF坐标系
/// @param body_lla     相机所在位置 经纬高坐标系
/// @param rvec         相机的旋转向量
/// @param cam_ins      相机的内参 fx, fy, cx, cy
/// @return             图像上的点
template <typename T>
Vector<T, 2> projection2pixel(const Vector<T, 3>& p_ecef, const Vector<T, 3>& body_ecef,
                              const Vector<T, 3>& body_lla,
                              const Vector<T, 3>& rvec, const Vector<T, 4>& cam_ins) {
    Vector<T, 3> p_ecef_relative = p_ecef - body_ecef;
    Vector<T, 3> p_ned = ecef2ned(p_ecef_relative, body_lla);
    Vector<T, 2> pixel = ned2pixel(p_ned, rvec, cam_ins);
    return pixel;
}
#endif  // COORDINATE_TRANSFORM_HPP
