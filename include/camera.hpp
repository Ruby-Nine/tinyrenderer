#pragma once

#include <eigen3/Eigen/Eigen>

class Camera{
public:
    Eigen::Vector3f eye_pos; // 相机位置
    Eigen::Vector3f look_at; // 相机朝向
    Eigen::Vector3f up; // 相机上方向
    float fov; // 视场角
    float aspect_ratio;
    float zNear; // 近裁剪面
    float zFar; // 远裁剪面

    Camera(){};
    Camera(Eigen::Vector3f eye, Eigen::Vector3f look, Eigen::Vector3f up, float fov, float aspect_ratio, float near, float far) : 
        eye_pos(eye), look_at(look), up(up), fov(fov), aspect_ratio(aspect_ratio), zNear(near), zFar(far){};
};