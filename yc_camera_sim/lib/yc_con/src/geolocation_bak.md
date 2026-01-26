```cpp
    // Note: lcy BEGIN -----------------------------------------

    constexprdoublefx=1960e-3;

    constexprdoublefy=1960e-3;

    constexprdoublecx= (5120-1) /2.0;

    constexprdoublecy= (4096-1) /2.0;

    Eigen::Vector3dbody_lla{AC_Position_pi.Lat*PI_Agl, AC_Position_pi.Lon*PI_Agl, AC_Position_pi.Alt};

    double          yaw        =AttitudeAC_pi.Yaw;   // 航向角

    double          pitch      =AttitudeAC_pi.Pitch; // 俯仰角

    double          roll       =AttitudeAC_pi.Roll;  // 横滚角

    double          depression= (param_Compute_Input_Fromfpga.rtime_pitch_frame+90) *Agl_PI;

    double          azimuth    = (param_Compute_Input_Fromfpga.rtime_direction_frame+90) *Agl_PI;

    Eigen::Vector3drvec=rot::calcRotationVector(yaw, pitch, roll, depression, azimuth, true);

    GeolocatorLOSgeolocator(body_lla, fx, fy, cx, cy, rvec);

    // 中心 左上 右上 左下 右下

    Eigen::Vector2dpx_center, px_lefttop, px_righttop, px_leftdown, px_rightdown;

    px_center    =Eigen::Vector2d(cx, cy);

    px_lefttop   =Eigen::Vector2d(0, 0);

    px_righttop  =Eigen::Vector2d(5120-1, 0);

    px_leftdown  =Eigen::Vector2d(0, 4096-1);

    px_rightdown=Eigen::Vector2d(5120-1, 4096-1);

    Eigen::Vector3dlla_center, lla_lefttop, lla_righttop, lla_leftdown, lla_rightdown;

    lla_center   =geolocator.get_target_lla(px_center, tar_high);

    lla_lefttop  =geolocator.get_target_lla(px_lefttop, tar_high);

    lla_righttop=geolocator.get_target_lla(px_righttop, tar_high);

    lla_leftdown=geolocator.get_target_lla(px_leftdown, tar_high);

    param_Compute_Output.image_center_latitude        =lla_center[0];

    param_Compute_Output.image_center_longitude       =lla_center[1];

    param_Compute_Output.A818_ImageCenterHeight       =std::round(lla_center[2]);

    param_Compute_Output.imaging_left_up_latitude     =lla_lefttop[0];

    param_Compute_Output.imaging_left_up_longitude    =lla_lefttop[1];

    param_Compute_Output.imaging_right_up_latitude    =lla_righttop[0];

    param_Compute_Output.imaging_right_up_longitude   =lla_righttop[1];

    param_Compute_Output.imaging_left_down_latitude   =lla_leftdown[0];

    param_Compute_Output.imaging_left_down_longitude  =lla_leftdown[1];

    param_Compute_Output.imaging_right_down_latitude  =lla_rightdown[0];

    param_Compute_Output.imaging_right_down_longitude=lla_rightdown[1];

    // Note: lcy END -------------------------------------------
    ```
