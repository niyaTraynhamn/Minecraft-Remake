#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include "blockStateData.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>       // glm::mat4

#include <string>
#include <cmath>    

#include <iostream>

//This file is for our material class which will handle our textures and shaders for our blocks

class MeshHandle;      // fwd decl (avoid heavy includes here)
class Shader;          // your engine/render/gl/shaderClass.hpp
class Texture;         // your engine/render/gl/textureClass.hpp


struct DrawCtx {
    glm::mat4 model;
    // later: camera UBO binding, pass type, time, etc.
};


// Creating a interface for materials
struct IMaterial {
    virtual void bind(const BlockState& b, const DrawCtx& ctx) const = 0;         // bind program + per-object uniforms
    virtual void draw(const MeshHandle& m) const = 0;      // issue glDraw* calls
    virtual ~IMaterial() = default; // virtual destructor for proper cleanup
};

/*This will handle the material, so we can call the textue from our shaderClass and it will get the texture and either map it
to the side or to the top or bottom of the cube*/
struct BlockMaterial : IMaterial {   
    // // Textured block (sides + top/bottom) — two draws with one VAO
    Texture* side = nullptr;    // GL texture handle (atlas or single)pointer so setMaterial works
    Texture* surface = nullptr;   //This will be the top and bottom textures of our cube
    //Texture* overlay = nullptr;
    Shader* shader  = nullptr; // not owned this is getting the shader we are using from our vert and frag files

    bool useTint = false; // Determine if tinting is used for this material
    glm::vec3 tint = glm::vec3(1.0f); // Default tint color (white, no tint)

    // If your mesh uses different ranges, customize these:
    int sidesCount = 24;   // first  24 indices (4 sides)
    int topBottomCount = 12;   // next   12 indices (top+bottom)
    int topBottomOffsetIdx = 24;   // offset in indices where top/bottom

    void bind(const BlockState& b, const DrawCtx& ctx) const override; // bind program + per-object uniforms
    void draw(const MeshHandle& mesh) const override; // issue glDraw* calls

};

// Creating a struct for the light material, Unlit/emissive light gizmo — one draw, positions only in VS
struct lightMaterial : IMaterial {
    Shader* shader = nullptr; // not owned this is getting the shader we are using from our vert and frag files
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Default white light

    void bind(const BlockState& b, const DrawCtx& ctx) const override;
    void draw(const MeshHandle& mesh) const override;
};

#endif