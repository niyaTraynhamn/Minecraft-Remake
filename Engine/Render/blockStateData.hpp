#ifndef BLOCKSTATE_CLASS_H
#define BLOCKSTATE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>    
#include <iostream>

//Creating the block type refernce IDs/names (really we are just naming the blocks)
enum class BlockType { 
    Grass, 
    Leaves,
    Tinted_glass,
    Stained_glass,
    Dirt, 
    Oak_log, 
    Oak_log_top,
    Stone, 
    Stone_top,
    Glass,
    Light
};

//Creating a struct to determine what state the block is in if it's transparent or if it's solid
struct BlockState {
    BlockType type;  // what kind of block this is
    bool      solid; // does it block movement / occlude faces
    bool      transparent; // affects render order & depth writes - does it need to be drawn with blending
    //bool      overlay;  // does it have an overlay texture (like grass)
    // If you’re not on a texture atlas yet, you can ignore this or store the GL texture ID here.
    // For now we'll let the renderer own the texture.
    BlockState(BlockType t, bool s, bool tr) : type(t), solid(s), transparent(tr) {}
};

#endif

