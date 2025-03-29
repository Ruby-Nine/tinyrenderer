#include "global.hpp"
#include "tgaimage.hpp"
#include "rasterizer.hpp"
#include "shader.hpp"
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

int main(int argc, char** argv) {
	std::string output = (argc > 1)?argv[1]:"./default.cpp";
	// Model model("../obj/african_head.obj");
	Shader shader(1024, 1024, TGAImage::RGB);
	// shader.render_wireframe(model);
	Eigen::Vector3f a(200, 200, 0);
	Eigen::Vector3f b(300, 500, 0);
	Eigen::Vector3f c(600, 400, 0);
	shader.render_triangle(a, b, c, white);
	shader.save_images(output);
	return 0;
}