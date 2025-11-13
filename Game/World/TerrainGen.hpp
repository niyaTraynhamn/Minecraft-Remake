#ifndef TERRAIN_CLASS_H
#define TERRAIN_CLASS_H

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\blockStateData.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\textureClass.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>       // glm::mat4
#include <glm/gtc/matrix_transform.hpp> //fro tanslate

#include <string>
#include <vector>
#include <cmath>    

#include <iostream>

struct Terrain {
    static std::vector<glm::mat4> makeFlatGrid(int sizeX, int sizeZ, float y = 0.0f) {
        std::vector<glm::mat4> M;
        M.reserve(sizeX * sizeZ);
        const int hx = sizeX / 2;
        const int hz = sizeZ / 2;
        for (int x = -hx; x < sizeX - hx; ++x) {
            for (int z = -hz; z < sizeZ - hz; ++z) {
                glm::mat4 m(1.0f);
                m = glm::translate(m, glm::vec3((float)x, y, (float)z));
                M.push_back(m);
            }
        }
        return M;
    }
};

#endif