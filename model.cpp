#include "model.hpp"

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


Model::Model(std::string path){
    std::ifstream ifs;
    ifs.open(path, std::ios::in); 
    if(!ifs.is_open()){
        std::cerr << "Error: Cannot open file " << path << std::endl;
        return;
    }

    std::vector<Vec3f> verts; // 顶点坐标
    std::vector<Vec2f> uvs; // 纹理坐标
    std::vector<Vec3f> norms; // 法线坐标

    std::string line;
    int line_count = 0;
    while(std::getline(ifs, line)){
        line_count++;
        // std::cout << line << std::endl; 
        auto pattern = split(line, " ");
        if(pattern.size() == 0){
            continue;
        }
        if(pattern[0] == "v"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Vec3f v = Vec3f(std::stof(pattern[1]), std::stof(pattern[2]), std::stof(pattern[3]));
            verts.emplace_back(v);
        }else if(pattern[0] == "vt"){
            if(pattern.size() < 3){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Vec2f vt = Vec2f(std::stof(pattern[1]), std::stof(pattern[2]));
            uvs.push_back(vt);
        }else if(pattern[0] == "vn"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Vec3f vn = Vec3f(std::stof(pattern[1]), std::stof(pattern[2]), std::stof(pattern[3]));
            norms.push_back(vn);
        }else if(pattern[0] == "f"){
            if(pattern.size() < 4){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            auto idx1= split(pattern[1], "/");
            auto idx2 = split(pattern[2], "/");
            auto idx3 = split(pattern[3], "/");
            if(idx1.size() < 3 || idx2.size() < 3 || idx3.size() < 3){
                std::cerr << "Error: Invalid vertex format at line " << line_count << std::endl;
                continue;
            }
            Point p1(verts[std::stoi(idx1[0])-1], uvs[std::stoi(idx1[1])-1], norms[std::stoi(idx1[2])-1]);
            Point p2(verts[std::stoi(idx2[0])-1], uvs[std::stoi(idx2[1])-1], norms[std::stoi(idx2[2])-1]);
            Point p3(verts[std::stoi(idx3[0])-1], uvs[std::stoi(idx3[1])-1], norms[std::stoi(idx3[2])-1]);
            Triangle triangle(p1, p2, p3);
            triangles.emplace_back(triangle);
        }
    }
}