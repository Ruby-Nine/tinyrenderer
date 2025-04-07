#include "rasterizer.hpp"
#include <cmath>
#include "global.hpp"
#include <iostream>

Eigen::Matrix4f generate_rotation_matrix(Eigen::Vector3f axis, float angle){
    float rad = PI * angle / 180;

    Eigen::Matrix3f cross_matrix;
    cross_matrix << 
        0, -axis[2], axis[1],
        axis[2], 0, -axis[0],
        -axis[1], axis[0], 0;
    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();

    Eigen::Matrix3f rotation_matrix = I + (1-cos(rad)) * cross_matrix * cross_matrix + sin(rad) * cross_matrix;

    Eigen::Matrix4f rotation_matrix4f = Eigen::Matrix4f::Identity();
    rotation_matrix4f.block<3,3>(0, 0) = rotation_matrix;

    return rotation_matrix4f;
}


Rasterizer::Rasterizer(Camera &camera){
    Eigen::Vector3f &eye_pos = camera.eye_pos;
    Eigen::Vector3f &look_at = camera.look_at; // 相机朝向
    Eigen::Vector3f &up = camera.up; // 相机上方向
    float fov = camera.fov * PI / 180; // 视场角
    float &aspect_ratio = camera.aspect_ratio;
    float &zNear = camera.zNear; // 近裁剪面
    float &zFar = camera.zFar; // 远裁剪面

    Eigen::Matrix4f view_matrix;
    Eigen::Vector3f r = look_at.cross(up).normalized();

    view_matrix <<
        r[0], r[1], r[2], -eye_pos[0],
        up[0], up[1], up[2], -eye_pos[1],
        -look_at[0], -look_at[1], -look_at[2], -eye_pos[2],
        0, 0, 0, 1;
    
    std::cout << "view_matrix: " << std::endl << view_matrix << std::endl;

    Eigen::Matrix4f perspective_matrix;
    float height = tan(fov) * zNear * 2;
    float width = height * aspect_ratio;

    perspective_matrix << 
        -zNear, 0, 0, 0,
        0, -zNear, 0, 0,
        0, 0, -zNear - zFar, -zNear * zFar,
        0, 0, 1, 0;

    std::cout << "perspective_matrix: " << std::endl << perspective_matrix << std::endl;

    Eigen::Matrix4f viewport_matrix;
    viewport_matrix << 
        2/width, 0, 0, 0,
        0, 2/height, 0, 0,
        0, 0, 2/(zFar-zNear), (zFar - zNear)/2,
        0, 0, 0, 1;

    std::cout << "viewport_matrix: " << std::endl << viewport_matrix << std::endl;

    MVP_matrix = viewport_matrix * perspective_matrix * view_matrix;

    std::cout << "MVP_matrix: " << std::endl << MVP_matrix << std::endl;
}