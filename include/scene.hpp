#pragma once

#include <eigen3/Eigen/Eigen>
#include <string>
#include <vector>
#include "triangle.hpp"
#include "camera.hpp"



class Scene{
public:
    Scene() : camera(Eigen::Vector3f(0.f, 0.f, -1.f), Eigen::Vector3f(0.f, 0.f, 0.f), Eigen::Vector3f(0.f, 1.f, 0.f), 45.f, 0.1f, 100.f) {};
    ~Scene(){};

    Camera camera; // 相机    
    MeshTriangle mesh;
};
