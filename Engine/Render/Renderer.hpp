#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "blockStateData.hpp"
#include "meshHandle.hpp"
#include "Material.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\textureClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\Material.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>       // glm::mat4

#include <string>
#include <cmath>    

#include <iostream>

#pragma once
#include "Material.hpp"
#include "MeshHandle.hpp"

class Renderer {
public:
    explicit Renderer(const MeshHandle& mesh) : mesh_(&mesh) {}

    void draw(const IMaterial& mat, const BlockState& block, const glm::mat4& model) const;

private:
    const MeshHandle* mesh_{};
};



#endif



// /*This will handle the material, so we can call the textue from our shaderClass and it will get the texture and either map it
// to the side or to the top or bottom of the cube*/
// struct Material {   
//     //get rid of these 
//     Texture* side = nullptr;    // GL texture handle (atlas or single)pointer so setMaterial works
//     Texture* surface = nullptr;   //This will be the top and bottom textures of our cube
//     //Texture* overlay = nullptr;
//     Shader* shader  = nullptr; // not owned this is getting the shader we are using from our vert and frag files
// };

// struct lightMaterial {
//     lightShader* shader = nullptr; // not owned this is getting the shader we are using from our vert and frag files
//     glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Default white light
// };

// //Creating the class
// class Renderer {
// public:
//     // Constructor in initalizer list this will basically intalize the object and refernce the mesh and material that will be added.
//     Renderer(const MeshHandle& mesh, const Material& mat) : mesh_(&mesh), mat_(&mat) {}

//     // Drawing the block to the window
//     void draw(const BlockState& b, const glm::mat4& model) const;

//     // If you later change textures/shader at runtime (not used now**)
//     void setMaterial(const Material& m) { mat_ = &m; }

// private:
//     //Creating our objects for the mesh and the material
//     const MeshHandle* mesh_; // reference; renderer does NOT own the GPU buffers
//     const Material* mat_;  // non-owning handles inside
//     const lightMaterial* lightMat_;  // non-owning handles inside
// };

// #endif
