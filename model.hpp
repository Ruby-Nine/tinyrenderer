#pragma once
#include"geometry.hpp"
#include <vector>
#include <fstream>
#include <string>


class Point{
public:
    Vec3f pos; // 顶点坐标
    Vec2f uv; // 纹理坐标
    Vec3f norm; // 法线坐标
    Point() : pos(0.f, 0.f, 0.f), uv(0.f, 0.f), norm(0.f, 0.f, 0.f){};
    Point(Vec3f p, Vec2f uv, Vec3f n) : pos(p), uv(uv), norm(n){};
};

class Triangle{
public:
    Point v[3]; // 三角形的三个顶点
    Triangle(Point p0, Point p1, Point p2){
        v[0] = p0;
        v[1] = p1;
        v[2] = p2;
    };
};

class Model{
private:
    std::vector<Triangle> triangles; // 三角形列表

public:
    Model(std::string fpath);
    std::vector<Triangle> get_triangles(){return triangles;};
};