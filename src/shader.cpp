#include "shader.hpp"
#include "global.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>


// 优化方案1： 把比例提到循环外
void Shader::line(int x0, int y0, int x1, int y1, TGAColor color) {
	bool steer = false;

	if(abs(x0-x1) < abs(y0-y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steer = true;
	}

	if(x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float div = (y1-y0) / float(x1-x0);
	for (int x=x0; x<x1; x+=1) {
		int y = y0 + div*(x-x0);
		if(steer) {
			image.set(y, x, color);
		}else{
			image.set(x, y, color);
		}
	}
}


// 优化方案1： 使用整数加法
void Shader::line_algo2(int x0, int y0, int x1, int y1, TGAColor color) {
	bool steer = false;

	if(abs(x0-x1) < abs(y0-y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steer = true;
	}

	if(x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int y_forward = y1 - y0 > 0 ? 1 : -1;

	float derror = abs(dy*2);
    float error = 0.f;
    int y = y0;

	for (int x=x0; x<x1; x+=1) {
		if(steer) {
			image.set(y, x, color);
		}else{
			image.set(x, y, color);
		}

        error += derror;
        if(error >= dx) {
            y += y_forward;
            error -= dx*2;
        }
	}
}

void Shader::render_wireframe_triangle(Triangle &triangle){
	Eigen::Vector3f v0 = triangle.v[0].pos;
	Eigen::Vector3f v1 = triangle.v[1].pos;
	Eigen::Vector3f v2 = triangle.v[2].pos;

	Eigen::Matrix3f scale_matrix;
	scale_matrix <<
		0.5f*image.get_width(), 0, 0,
		0, 0.5f*image.get_height(), 0,
		0, 0, 1;
	v0 = scale_matrix * (v0 + Eigen::Vector3f(1, 1, 0));
	v1 = scale_matrix * (v1 + Eigen::Vector3f(1, 1, 0));
	v2 = scale_matrix * (v2 + Eigen::Vector3f(1, 1, 0));

	line(v0[0], v0[1], v1[0], v1[1], white);
	line(v1[0], v1[1], v2[0], v2[1], white);
	line(v2[0], v2[1], v0[0], v0[1], white);
}

void Shader::render_triangle(Eigen::Vector3f v1, Eigen::Vector3f v2, Eigen::Vector3f v3, TGAColor color){
	int xmin = std::min(v1[0], std::min(v2[0], v3[0]));
	int xmax = std::max(v1[0], std::max(v2[0], v3[0]));
	int ymin = std::min(v1[1], std::min(v2[1], v3[1]));
	int ymax = std::max(v1[1], std::max(v2[1], v3[1]));

	Eigen::Vector3f e1 = v2 - v1;
	Eigen::Vector3f e2 = v3 - v2;
	Eigen::Vector3f e3 = v1 - v3;

	for(int x=xmin; x<=xmax; ++x){
		for(int y=ymin; y<=ymax; ++y){
			Eigen::Vector3f p(x, y, 0.f);
			Eigen::Vector3f ep1 = p - v1;
			Eigen::Vector3f ep2 = p - v2;
			Eigen::Vector3f ep3 = p - v3;

			float dp1 = ep1.cross(e1)[2];
			float dp2 = ep2.cross(e2)[2];
			float dp3 = ep3.cross(e3)[2];

			if(dp1 == 0 || dp2 == 0 || dp3 == 0 || 
			(dp1 > 0 && dp2 > 0 && dp3 > 0) ||
			(dp1 < 0 && dp2 < 0 && dp3 < 0)){
				image.set(x, y, color);
			}
		}
	}
}

void Shader::render_wireframe(MeshTriangle &mesh){
	auto t = mesh.get_triangle();
	while(t){
		render_wireframe_triangle(*t);
		t = mesh.get_triangle();
	}
}


Shader::~Shader() {
}