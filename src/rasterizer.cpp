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
    float &fov = camera.fov; // 视场角
    float &aspect_ratio = camera.aspect_ratio;
    float &zNear = camera.zNear; // 近裁剪面
    float &zFar = camera.zFar; // 远裁剪面

    Eigen::Vector4f camera_move_matrix;
    camera_move_matrix <<
        0, 0, 0, -eye_pos[0],
        0, 0, 0, -eye_pos[1],
        0, 0, 0, -eye_pos[2],
        0, 0, 0, 1;

    // 绕半程向量旋转180°到目标向量
    Eigen::Vector4f camera_rotate_matrix;
    if(look_at[0] == 0 && look_at[1] == 0){
        camera_rotate_matrix = Eigen::Vector4f::Identity();
        if(look_at[2] > 0){
            camera_rotate_matrix(3, 3) = -1.f;
        } 
    }else{
        Eigen::Vector3f z_axis(0, 0,-1);
        Eigen::Vector3f half_v = (look_at + z_axis).normalized();
        camera_rotate_matrix = generate_rotation_matrix(half_v, 180);
    }

    float cos_theta = up[1];
    float sin_theta = -up[0];

    Eigen::Vector4f look_rotation_matrix;
    look_rotation_matrix << 
        cos_theta, sin_theta, 0, 0,
        -sin_theta, cos_theta, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;

    Eigen::Matrix4f view_matrix = camera_move_matrix * camera_rotate_matrix.transpose() * look_rotation_matrix.transpose();

    Eigen::Matrix4f perspective_matrix;
    float height = fov * zNear * 2;
    float width = height * aspect_ratio;

    perspective_matrix << 
        zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -zNear * zFar,
        0, 0, 1, 0;

    Eigen::Matrix4f viewport_matrix;
    viewport_matrix << 
        2/width, 0, 0, 0,
        0, 2/height, 0, 0,
        0, 0, 2/(zNear-zFar), 0,
        0, 0, 0, 1;

    MVP_matrix = viewport_matrix * perspective_matrix * view_matrix;
}