#pragma once

#include <eigen3/Eigen/Eigen>
#include <vector>
#include <memory>
#include "triangle.hpp"

struct MeshData{
    Eigen::Vector3i vert_idx;
    Eigen::Vector3i uv_idx;
    Eigen::Vector3i norm_idx;
    MeshData(Eigen::Vector3i v_i, Eigen::Vector3i u_i, Eigen::Vector3i n_i):vert_idx(v_i), uv_idx(u_i), norm_idx(n_i){};
};

struct Point{
    Eigen::Vector3f pos; // 3D坐标
    Eigen::Vector2f uv; // 纹理坐标
    Eigen::Vector3f norm; // 法线
    Point(Eigen::Vector3f p, Eigen::Vector2f u, Eigen::Vector3f n):pos(p), uv(u), norm(n){};
};

class Triangle{
public:
    std::vector<Point> v;
    Triangle(Eigen::Vector3f p[], Eigen::Vector2f u[], Eigen::Vector3f n[]){
        v = std::vector<Point>({
            Point(p[0], u[0], n[0]),
            Point(p[1], u[1], n[1]),
            Point(p[2], u[2], n[2])
        });
    };
};

class MeshTriangle{
private:
    unsigned int count;

public:
    std::vector<Eigen::Vector3f> verts;
    std::vector<Eigen::Vector2f> uvs;
    std::vector<Eigen::Vector3f> norms;
    std::vector<MeshData> idxs;

    MeshTriangle(){count=0;};

    void load_mesh(std::string path);

    std::shared_ptr<Triangle> get_triangle();
};