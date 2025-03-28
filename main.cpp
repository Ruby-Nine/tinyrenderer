#include "global.hpp"
#include "tgaimage.hpp"
#include "rasterizer.hpp"
#include "model.hpp"
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>

void test_line_performance() {
	int width=64;
	int height=64;
	Rasterizer rasterizer(width, height, TGAImage::RGB);

	std::srand(std::time({}));
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < (1<<24); i++) {
		int ax = rand()%width, ay = rand()%height;
        int bx = rand()%width, by = rand()%height;
        rasterizer.line(ax, ay, bx, by, { static_cast<unsigned char>(rand()%255), 
			static_cast<unsigned char>(rand()%255), static_cast<unsigned char>(rand()%255), static_cast<unsigned char>(rand()%255)});
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Time: " << duration.count() << "ms" << std::endl;
	rasterizer.save_images("line_algo1.tga");
}

int main(int argc, char** argv) {
	Model model("../obj/african_head.obj");
	Rasterizer rasterizer(1024, 1024, TGAImage::RGB);
	rasterizer.render_wireframe(model);
	return 0;
}