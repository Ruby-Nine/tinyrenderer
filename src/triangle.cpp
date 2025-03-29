#include "triangle.hpp"
#include <fstream>
#include <iostream>

const std::vector<std::string> split(const std::string& str, const std::string& pattern) {
    std::vector<std::string> result;
    std::string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end-begin)); 
        }    
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.emplace_back(str.substr(begin));
    }
    return result;        
}


void MeshTriangle::load_mesh(std::string fpath){
    std::ifstream ifs;
    ifs.open(fpath, std::ios::in); 
    if(!ifs.is_open()){
        std::cerr << "Error: Cannot open file " << fpath << std::endl;
        return;
    }

    std::string line;
    int line_count = 0;
    while(std::getline(ifs, line)){
        line_count++;
        auto pattern = split(line, " ");
        if(pattern.size() == 0){
            continue;
        }
        if(pattern[0] == "v"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Eigen::Vector3f v = Eigen::Vector3f(std::stof(pattern[1]), std::stof(pattern[2]), std::stof(pattern[3]));
            verts.emplace_back(v);
        }else if(pattern[0] == "vt"){
            if(pattern.size() < 3){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Eigen::Vector2f vt = Eigen::Vector2f(std::stof(pattern[1]), std::stof(pattern[2]));
            uvs.push_back(vt);
        }else if(pattern[0] == "vn"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Eigen::Vector3f vn = Eigen::Vector3f(std::stof(pattern[1]), std::stof(pattern[2]), std::stof(pattern[3]));
            norms.push_back(vn);
        }else if(pattern[0] == "f"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid face format at line " << line_count << std::endl;
                continue;
            }
            auto vert_pattern = split(pattern[1], "/");
            auto uv_pattern = split(pattern[1], "/");
            auto norm_pattern = split(pattern[1], "/");
            if(vert_pattern.size() !=3 && uv_pattern.size() !=3 && norm_pattern.size() !=3){
                std::cerr << "Error: Invalid face format at line " << line_count << std::endl;
                continue;
            }

            Eigen::Vector3i vert_idx(
                std::stoi(vert_pattern[0]),
                std::stoi(vert_pattern[1]),
                std::stoi(vert_pattern[2])
            );
            Eigen::Vector3i uv_idx(
                std::stoi(uv_pattern[0]),
                std::stoi(uv_pattern[1]),
                std::stoi(uv_pattern[2])
            );
            Eigen::Vector3i norm_idx(
                std::stoi(norm_pattern[0]),
                std::stoi(norm_pattern[1]),
                std::stoi(norm_pattern[2])
            );
            idxs.emplace_back(MeshData(vert_idx, uv_idx, norm_idx));
        }
    }
}

std::shared_ptr<Triangle> MeshTriangle::get_triangle(){
    if(count >= idxs.size()){
        return nullptr; // Return nullptr if no more triangles are available
    }
    Eigen::Vector3i vert_idx = idxs[count].vert_idx;
    Eigen::Vector3i uv_idx = idxs[count].uv_idx;
    Eigen::Vector3i norm_idx = idxs[count].norm_idx;

    Eigen::Vector3f t_verts[3] = {
        verts[vert_idx[0]],
        verts[vert_idx[1]],
        verts[vert_idx[2]]
    };
    Eigen::Vector2f t_uvs[3] = {
        uvs[uv_idx[0]],
        uvs[uv_idx[1]],
        uvs[uv_idx[2]]
    };
    Eigen::Vector3f t_norms[3] = {
        norms[norm_idx[0]],
        norms[norm_idx[1]],
        norms[norm_idx[2]]
    };
    count++;
    return std::make_shared<Triangle>(Triangle(t_verts, t_uvs, t_norms)); // Create a triangle object with the vertices, uvs, and normals
}