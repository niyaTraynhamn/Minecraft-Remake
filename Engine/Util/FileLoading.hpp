#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace FileLoading {

inline std::string loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << '\n';
        return "";
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

} // namespace FileLoading




