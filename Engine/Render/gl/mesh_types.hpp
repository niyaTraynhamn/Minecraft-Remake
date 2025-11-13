// Engine/Render/mesh_types.hpp
#pragma once

#include <cassert>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdint>

//Creating a struct to hold the vertex data for our mesh
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;     // keep if you use it; otherwise remove in all code
    glm::vec2 TexCoords;
};
static_assert(sizeof(Vertex) == 44, "Vertex should be 44 bytes");


//Create a struct to hold the ranges for easy access when drawing subsets of an object.
struct FaceRanges {
    // North (front, +Z)
    std::uint32_t northStart; 
    std::uint32_t northCount;

    // South (back, -Z)
    std::uint32_t southStart;
    std::uint32_t southCount;

    // East (right, +X)
    std::uint32_t eastStart;
    std::uint32_t eastCount;

    // West (left, -X)
    std::uint32_t westStart;
    std::uint32_t westCount;

    // Top (+Y)
    std::uint32_t topStart;
    std::uint32_t topCount;

    // Bottom (-Y)
    std::uint32_t bottomStart;
    std::uint32_t bottomCount;

    // Sides (+Z, -Z, +X, -X)
    std::uint32_t sidesOverlayStart;
    std::uint32_t sidesOverlayCount;

    // Top (+Y)
    std::uint32_t topOverlayStart;
    std::uint32_t topOverlayCount;
     
};