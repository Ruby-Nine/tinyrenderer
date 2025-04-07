#pragma once

#include "tgaimage.hpp"
#include "triangle.hpp"
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <memory>
#include <vector>
#include <limits>


class Shader {
private:
    TGAImage image;
    Eigen::Vector3f lightdir;
    std::vector<std::vector<float>> zBuffer;


public:
    Shader(int width, int height, TGAImage::Format format) : image(width, height, format), lightdir(0.f, 0.f, -1.f), 
        zBuffer(width, std::vector<float>(height, -std::numeric_limits<float>::max())){};
    Shader(){
        Shader(64, 64, TGAImage::RGB);
    };
    ~Shader();

    TGAImage get_image() { return image;};
    void save_images(const std::string path) { image.write_tga_file(path.c_str()); };

    void line(int x0, int y0, int x1, int y1, TGAColor color);
    void line_algo2(int x0, int y0, int x1, int y1, TGAColor color);
    void render_wireframe_triangle(Triangle &triangle);
    void render_triangle(Triangle &triangle);
    void render_triangle(Eigen::Vector3f v1, Eigen::Vector3f v2, Eigen::Vector3f v3, TGAColor color);
    void render_triangle(Triangle& triangle, TGAColor color);
    void render_wireframe(MeshTriangle &mesh);
};