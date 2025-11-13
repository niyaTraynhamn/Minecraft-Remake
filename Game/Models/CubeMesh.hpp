#ifndef CUBEMESH_CLASS_H
#define CUBEMESH_CLASS_H

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\mesh_types.hpp"

#include <glm/glm.hpp> // Add this include for glm::vec3 and glm::vec2
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>    // std::size_t
#include <cstdint>    // std::uint32_t
#include <vector>   

#include <iostream>

/* The job of the cubeMesh file is is to define the positions, colors/UVs for each vertex. Define the indices that connect the vertices
into triangles. And, Define the face ranges of the cube (which indices are sides, top, bottom, overlay). This module is the single 
source of truth for our cube. */


//Creating a struct to hold the ranges for easy access when drawing subsets of the cube.
struct cubeFaceRanges {
    // North (front, +Z)
    std::uint32_t northStart = 0; //We won't use unsigned int as it is 64 bit and we only need 32 bit
    std::uint32_t northCount  = 6;

    // South (back, -Z)
    std::uint32_t southStart = 6;
    std::uint32_t southCount = 6;

    // East (right, +X)
    std::uint32_t eastStart = 12;
    std::uint32_t eastCount = 6;

    // West (left, -X)
    std::uint32_t westStart = 18;
    std::uint32_t westCount = 6;

    // Top (+Y)
    std::uint32_t topStart = 24;
    std::uint32_t topCount = 6;

    // Bottom (-Y)
    std::uint32_t bottomStart = 30;
    std::uint32_t bottomCount = 6;

    // If possible, add overlays unsure if it should be its own structure needs to be clarified
};

//Creating the cubeMesh object
class CubeMesh {
public:
    // Using vectors for easy management of dynamic arrays rather than raw arrays as it simplifies memory management and resizing.
    std::vector<Vertex> vertices;   // This stores the --> position, color, uv, and normal
    std::vector<std::uint32_t> indices;   // This stores the index data

    cubeFaceRanges ranges{}; //We are taking the already created values of the cube from our structure

    std::size_t floatsPerVertex = 8; //pos = 3 + color = 3 + uv = 2 = 8 floats per vertex.
    std::size_t vertexStrideBytes = floatsPerVertex * sizeof(float); // size of each vertex in bytes

    //positionOffset, colorOffset, uvOffset are byte offsets; Again we are taking from the floatsPerVertex
    std::size_t positionOffsetBytes = 0;               // position starts at 0
    std::size_t colorOffsetBytes = 3 * sizeof(float); // color starts after 3 floats (position)
    std::size_t uvOffsetBytes = 6 * sizeof(float);    // uv starts after 6

    // Convenience getters we want to avoid storing duplicate of the counts we have
    std::size_t vertexCount() const; // 24 unique vertices for a cube (4 vertices per face * 6 faces) or vertices size/floatsPerVertex
    std::size_t indexCount() const; // 36 indices (2 triangles per face * 3 indices per triangle * 6 faces) or indices size

    // Factory method to build a standard unit cube this is so that we can call it in main.cpp without having to redefine the cube every time.
    static CubeMesh makeUnitCube();

};

#endif