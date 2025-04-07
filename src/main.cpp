#include "global.hpp"
#include "tgaimage.hpp"
#include "rasterizer.hpp"
#include "shader.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include <eigen3/Eigen/Eigen>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>

void test_line_performance() {
	int width=64;
	int height=64;
	Shader shader(width, height, TGAImage::RGB);

	std::srand(std::time({}));
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < (1<<24); i++) {
		int ax = rand()%width, ay = rand()%height;
        int bx = rand()%width, by = rand()%height;
        shader.line(ax, ay, bx, by, { static_cast<unsigned char>(rand()%255), 
			static_cast<unsigned char>(rand()%255), static_cast<unsigned char>(rand()%255), static_cast<unsigned char>(rand()%255)});
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Time: " << duration.count() << "ms" << std::endl;
	shader.save_images("line_algo1.tga");
}

void test_triangle_zbuffer(std::string output) {
	Shader shader(1024, 1024, TGAImage::RGB);
	// shader.render_wireframe(model);
	Eigen::Vector3f a(200, 200, 0);
	Eigen::Vector3f b(300, 500, 0);
	Eigen::Vector3f c(600, 400, 0);
	shader.render_triangle(a, b, c, white);
	Eigen::Vector3f d(600, 200, -100);
	Eigen::Vector3f e(300, 500, 0);
	Eigen::Vector3f f(200, 400, 100);
	shader.render_triangle(d, e, f, red);
	shader.save_images(output);
}

void test_render_triangle_wireframe(std::string output) {
	Camera camera(
		Eigen::Vector3f(0.f, 0.f, 2.f),
		Eigen::Vector3f(0.f, 0.f, -1.f),
		Eigen::Vector3f(0.f, 1.f, 0.f),
		45.f, 1.f, 1.f, 3.f
	);
	Scene scene1(camera);
	scene1.load_mesh("../obj/african_head.obj");
	scene1.onlywire_render(output);
}

void test_render_triangle(std::string output) {
	Camera camera(
		Eigen::Vector3f(0.f, 0.f, 2.f),
		Eigen::Vector3f(0.f, 0.f, -1.f),
		Eigen::Vector3f(0.f, 1.f, 0.f),
		45.f, 1.f, 1.f, 3.f
	);
	Scene scene1(camera);
	scene1.load_mesh("../obj/african_head.obj");
	scene1.render(output);
}

int main(int argc, char** argv) {
	std::string output = (argc > 1)?argv[1]:"./af_face.cpp";
	test_render_triangle(output);
	return 0;
}