#pragma once

#include <eigen3/Eigen/Eigen>
#include <string>
#include <vector>
#include "triangle.hpp"
#include "camera.hpp"
#include "rasterizer.hpp"
#include "global.hpp"
#include "shader.hpp"


class Scene{
public:
    Scene(Camera camera);
    Scene() : Scene(
        Camera(
            Eigen::Vector3f(0.f, 0.f, 1.f),
            Eigen::Vector3f(0.f, 0.f, -1.f),
            Eigen::Vector3f(0.f, 1.f, 0.f),
            45.f, 1.f, 0.1f, 100.f)
    ){};
    ~Scene(){};

    Camera camera; // 相机    
    MeshTriangle mesh;
    Rasterizer rasterizer;
    Shader shader;

    void load_mesh(std::string path){
        mesh.load_mesh(path);
    };

    void render(std::string output);
    void onlywire_render(std::string output);
};
