#pragma once

#include "tgaimage.hpp"
#include "model.hpp"
#include "geometry.hpp"
#include <cmath>
#include <memory>


class Rasterizer {
private:
    TGAImage image;
    Vec3f eye_pos;


public:
    Rasterizer() {Rasterizer(64, 64, TGAImage::RGB);};
    Rasterizer(int width, int height, TGAImage::Format format) : image(width, height, format), eye_pos(0.f, 0.f, -1.f) {};
    ~Rasterizer();

    TGAImage get_image() { return image;};
    void save_images(const char* path) { image.write_tga_file(path); };

    void line(int x0, int y0, int x1, int y1, TGAColor color);
    void line_algo2(int x0, int y0, int x1, int y1, TGAColor color);
    void render_wireframe_triangle(Triangle triangle);
    void render_triangle(Vec3i v1, Vec3i v2, Vec3i v3, TGAColor color);
    void render_wireframe(Model &model);
};