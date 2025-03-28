#include "rasterizer.hpp"
#include "global.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>


// 优化方案1： 把比例提到循环外
void Rasterizer::line(int x0, int y0, int x1, int y1, TGAColor color) {
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
void Rasterizer::line_algo2(int x0, int y0, int x1, int y1, TGAColor color) {
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

void Rasterizer::render_wireframe_triangle(Triangle triangle){
	Vec3f v0 = (triangle.v[0].pos + Vec3f(1, 1, 0)) * Vec3f(0.5f, 0.5f, 1) * Vec3f(image.get_width(), image.get_height(), 1);
	Vec3f v1 = (triangle.v[1].pos + Vec3f(1, 1, 0)) * Vec3f(0.5f, 0.5f, 1) * Vec3f(image.get_width(), image.get_height(), 1);
	Vec3f v2 = (triangle.v[2].pos + Vec3f(1, 1, 0)) * Vec3f(0.5f, 0.5f, 1) * Vec3f(image.get_width(), image.get_height(), 1);
	line(v0.x, v0.y, v1.x, v1.y, white);
	line(v1.x, v1.y, v2.x, v2.y, white);
	line(v2.x, v2.y, v0.x, v0.y, white);
}

void Rasterizer::render_wireframe(Model& model){
	for(auto &t: model.get_triangles()){
		render_wireframe_triangle(t);
	}
	save_images("wireframe.tga");	
}


Rasterizer::~Rasterizer() {
}