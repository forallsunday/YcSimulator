/**
 * @Author: Chongyang Liu
 * @Date:   2023-04-10 10:28:08
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2025-05-10 18:15:53
 */
#include <geolocation.h>
#include <wgs84.h>

#include <Eigen/Geometry>
#include <iostream>
#include <projective_geometry.hpp>

using namespace Eigen;

/// @brief 计算直线与球体的交点
/// @param o 直线上一点
/// @param d 直线方向(单位向量)
/// @param radius 球体半径(=1时为单位圆)
/// @return 交点，只返回第一个交点
template <typename T>
Vector<T, 3> line_sphere_intersection(
    const Vector<T, 3>& o, const Vector<T, 3>& d, T radius = T(1)) {
    auto w = o;
    auto a = d.dot(d);
    auto b = T(2) * d.dot(w);
    auto c = w.dot(w) - radius * radius;
    auto disc = b * b - T(4) * a * c;
    auto t1 = (-b - sqrt(disc)) / (T(2) * a);
    // // print to debug
    // std::cout << "------------------------------" << std::endl;
    // std::cout << "o: \n"
    //           << o << std::endl;
    // std::cout << "d: \n"
    //           << d << std::endl;
    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;
    // std::cout << "c: " << c << std::endl;
    // std::cout<< "disc: " << disc << std::endl;
    // only return the first intersection
    return o + t1 * d;
};

/// @brief 直线与椭球的交点
/// @param o 直线上一点
/// @param d 直线方向(单位向量)
/// @param a 椭球半轴
/// @param b 椭球半轴
/// @param c 椭球半轴
/// @return 直线与椭球交点，只返回第一个交点
template <typename T>
Vector<T, 3> line_ellipsoid_intersection(
    const Vector<T, 3>& o, const Vector<T, 3>& d, T& a, T& b, T& c) {
    Matrix<T, 3, 3> S, S_inv;
    S << a, T(0), T(0),
        T(0), b, T(0),
        T(0), T(0), c;
    S_inv << T(1. / a), T(0), T(0),
        T(0), T(1. / b), T(0),
        T(0), T(0), T(1. / c);
    Vector<T, 3> o0 = S_inv * o;
    Vector<T, 3> ds = S_inv * d;
    Vector<T, 3> pt_sphere = line_sphere_intersection(o0, ds);
    Vector<T, 3> pt_ellipsoid = S * pt_sphere;
    return pt_ellipsoid;
}

/// @brief 从相机发出的射线与地球的交点
/// @param body_ecef 载机ECEF坐标
/// @param direction 射线方向
/// @param alt_obj 目标高程
/// @return 从相机发出的射线与地球的交点
template <typename T>
Vector<T, 3> earth_intersaction(
    const Vector<T, 3>& body_ecef, const Vector<T, 3>& direction, const T& alt_obj) {
    T a, b, c;
    a = WGS84_a + alt_obj;
    b = a;
    c = WGS84__b + alt_obj;
    Vector<T, 3> d_normed = direction.normalized();
    return line_ellipsoid_intersection(body_ecef, d_normed, a, b, c);
}

// 计算两条直线的最近点对 not used
// l1 = p1 + d1
template <typename T>
void nearest_pts_skew_lines(const Vector<T, 3>& p1, const Vector<T, 3>& d1,
                            const Vector<T, 3>& p2, const Vector<T, 3>& d2,
                            Vector<T, 3>& c1, Vector<T, 3>& c2) {
    Vector<T, 3> n = d1.cross(d2);
    Vector<T, 3> n1 = d1.cross(n);
    Vector<T, 3> n2 = d2.cross(n);
    c1 = p1 + n2.dot(p2 - p1) / n2.dot(d1) * d1;
    c2 = p2 + n1.dot(p1 - p2) / n1.dot(d2) * d2;
}

GeolocatorLOS::GeolocatorLOS(Vector3d body_lla, Vector4d cam_ins, Vector3d rvec)
    : body_lla(body_lla), cam_ins(cam_ins), rvec(rvec) {
    this->body_ecef = lla2ecef(body_lla);
}

GeolocatorLOS::GeolocatorLOS(
    Vector3d body_lla, double fx, double fy, double cx, double cy, Vector3d rvec)
    : body_lla(body_lla), rvec(rvec) {
    this->body_ecef = lla2ecef(body_lla);
    this->cam_ins << fx, fy, cx, cy;
}

GeolocatorLOS::GeolocatorLOS(Vector3d body_lla, Matrix3d K, Matrix3d R)
    : body_lla(body_lla), K(K), R(R) {
    double fx, fy, cx, cy;
    fx = K(0, 0);
    fy = K(1, 1);
    cx = K(0, 2);
    cy = K(1, 2);
    this->cam_ins << fx, fy, cx, cy;

    Eigen::AngleAxisd aa(R);
    this->rvec = aa.angle() * aa.axis();
}

Vector3d GeolocatorLOS::get_target_ecef(const Vector2d& pp, const double alt_obj) {
    auto ray_d = ray_direction(pp, cam_ins, rvec, body_lla, body_ecef);
    return earth_intersaction(body_ecef, ray_d, alt_obj);
}

Vector3d GeolocatorLOS::get_target_lla(const Vector2d& pp, const double alt_obj) {
    return ecef2lla(get_target_ecef(pp, alt_obj));
}