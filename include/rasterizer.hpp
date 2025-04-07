#pragma once
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "camera.hpp"
#include "triangle.hpp"


class Rasterizer{
private:
    Eigen::Matrix4f MVP_matrix;
public:
    Rasterizer(){};
    Rasterizer(Camera &camera);
    ~Rasterizer(){};

    Eigen::Vector3f apply_MVP(Eigen::Vector3f &v){
        Eigen::Vector4f n_v = v.homogeneous();
        n_v = MVP_matrix*n_v;
        n_v = n_v / n_v[3];
        return n_v.head<3>();
    }

    Triangle apply_MVP(Triangle &triangle){
        Triangle new_triangle = triangle;
        for(int i=0; i<3; ++i){
            new_triangle.v[i].pos = apply_MVP(new_triangle.v[i].pos);
            new_triangle.v[i].norm = apply_MVP(new_triangle.v[i].norm);
        }
        return new_triangle;
    }
};
