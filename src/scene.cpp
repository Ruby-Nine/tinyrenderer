#include "scene.hpp"
#include <random>


Scene::Scene(Camera camera){
    this->camera = camera;
    rasterizer = Rasterizer(camera);
    shader = Shader(1024, 1024, TGAImage::RGB);
}


void Scene::render(std::string output){
    std::random_device rd;  // 真随机数种子（硬件依赖）
    std::mt19937 gen(rd()); // Mersenne Twister 伪随机数引擎
    std::uniform_int_distribution<int> dist(0, 255); // 均匀分布 [1, 100]

    auto triangle = mesh.get_triangle();
    while(triangle){
        auto t = rasterizer.apply_MVP(*triangle);
        // shader.render_triangle(t, TGAColor(dist(gen), dist(gen), dist(gen), 255));
        shader.render_triangle(*triangle);
        triangle = mesh.get_triangle();
    }
    shader.save_images(output);
};

void Scene::onlywire_render(std::string output){
    auto triangle = mesh.get_triangle();
    while(triangle){
        // auto t = rasterizer.apply_MVP(*triangle);
        // shader.render_triangle(t, TGAColor(dist(gen), dist(gen), dist(gen), 255));
        shader.render_wireframe_triangle(*triangle);
        triangle = mesh.get_triangle();
    }
    shader.save_images(output);
};