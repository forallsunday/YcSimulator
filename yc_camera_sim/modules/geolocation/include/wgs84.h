/**
 * @Author: Chongyang Liu
 * @Date:   2023-02-10 14:25:49
 * @Last Modified by:   Chongyang Liu
 * @Last Modified time: 2023-03-01 14:44:04
 */
//  Table 3.1: WGS 84  Four Defining Parameters
#ifndef WGS84_H
#define WGS84_H

#define WGS84_a 6378137.0                   // Semi-major Axis [m]
#define WGS84_f 1. / 298.257223563          // Flattening
#define WGS84_omega_E 7292115.0e-11         // Angular velocity of the Earth [rad/s]
#define WGS84_omega_E_GPS 7292115.1467e-11  // Angular velocity of the Earth [rad/s]
                                            // According to ICD-GPS-200

// Earth's Gravitational Constant [m^3/s^2]
// (mass of earth's atmosphere included)

#define WGS84_GM 3986004.418e8
// The WGS 84 GM value recommended for GPS receiver usage
// by the GPS interface control document (ICD-GPS-200)
// differs from the current refined WGS 84 GM value.
//
// Details for this difference can be read in the WGS84
// reference: 3.2.3.2 "Special Considerations for GPS"
#define WGS84_GM_GPS 3986005.0e8

// Table 3.3: WGS 84 Ellipsoid Derived Geometric Constants
#define WGS84__b 6356752.3142             // Semi-minor axis [m]
#define WGS84__ecc 8.1819190842622e-2     // First eccentricity
#define WGS84__ecc_sqrd 6.69437999014e-3  // First eccentricity squared

#endif // WGS84_H
