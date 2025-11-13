#include "CubeMesh.hpp"

//calling the make unit cube function
CubeMesh CubeMesh::makeUnitCube() {
    //calling the mesh class
    CubeMesh mesh;

    // 24 vertices (6 faces × 4 vertices each)
    // 24 vertices (6 faces × 4 verts), positions at ±0.5
    mesh.vertices = {
        // Front (+Z)
        {{-0.5f, -0.5f,  0.5f}, {0,0,1}, {1,1,1}, {0,0}},
        {{ 0.5f, -0.5f,  0.5f}, {0,0,1}, {1,1,1}, {1,0}},
        {{ 0.5f,  0.5f,  0.5f}, {0,0,1}, {1,1,1}, {1,1}},
        {{-0.5f,  0.5f,  0.5f}, {0,0,1}, {1,1,1}, {0,1}},

        // Back (−Z)
        {{ 0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {0,0}},
        {{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {1,0}},
        {{-0.5f,  0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {1,1}},
        {{ 0.5f,  0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {0,1}},

        // Left (−X)
        {{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {1,1,1}, {0,0}},
        {{-0.5f, -0.5f,  0.5f}, {-1,0,0}, {1,1,1}, {1,0}},
        {{-0.5f,  0.5f,  0.5f}, {-1,0,0}, {1,1,1}, {1,1}},
        {{-0.5f,  0.5f, -0.5f}, {-1,0,0}, {1,1,1}, {0,1}},

        // Right (+X)
        {{ 0.5f, -0.5f,  0.5f}, { 1,0,0}, {1,1,1}, {0,0}},
        {{ 0.5f, -0.5f, -0.5f}, { 1,0,0}, {1,1,1}, {1,0}},
        {{ 0.5f,  0.5f, -0.5f}, { 1,0,0}, {1,1,1}, {1,1}},
        {{ 0.5f,  0.5f,  0.5f}, { 1,0,0}, {1,1,1}, {0,1}},

        // Top (+Y)
        {{-0.5f,  0.5f,  0.5f}, {0,1,0}, {1,1,1}, {0,0}},
        {{ 0.5f,  0.5f,  0.5f}, {0,1,0}, {1,1,1}, {1,0}},
        {{ 0.5f,  0.5f, -0.5f}, {0,1,0}, {1,1,1}, {1,1}},
        {{-0.5f,  0.5f, -0.5f}, {0,1,0}, {1,1,1}, {0,1}},

        // Bottom (−Y)
        {{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,1,1}, {0,0}},
        {{ 0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,1,1}, {1,0}},
        {{ 0.5f, -0.5f,  0.5f}, {0,-1,0}, {1,1,1}, {1,1}},
        {{-0.5f, -0.5f,  0.5f}, {0,-1,0}, {1,1,1}, {0,1}},
    };

    // Fill in indices for the cube (two triangles per face)
    mesh.indices = {
        0,  1,  2,   0,  2,  3,    // front/north (+Z) 
        4,  5,  6,   4,  6,  7,    // back/south (-Z)
        8,  9, 10,   8, 10, 11,    // left/east  (+X)
        12, 13, 14,  12, 14, 15,   // right/west  (-X)
        16, 17, 18,  16, 18, 19,   // top (+Y)
        20, 21, 22,  20, 22, 23    // bottom (-Y)
    };

    // Define ranges (sides = first 24, top = next 6, bottom = last 6)
    // North (front, +Z)
    mesh.ranges.northStart  = 0;
    mesh.ranges.northCount  = 6;
    // South (back, -Z)
    mesh.ranges.southStart  = 6;
    mesh.ranges.southCount  = 6;
    // East (right, +X)
    mesh.ranges.eastStart   = 12;
    mesh.ranges.eastCount   = 6;
    // West (left, -X)
    mesh.ranges.westStart   = 18;
    mesh.ranges.westCount   = 6;
    // Top (+Y)
    mesh.ranges.topStart    = 24;
    mesh.ranges.topCount    = 6;
    // Bottom (-Y)
    mesh.ranges.bottomStart = 30;
    mesh.ranges.bottomCount = 6;

    return mesh;
}

//Return our Vertex count which should be 24
std::size_t CubeMesh::vertexCount() const {
    return vertices.size();
} 

//Return our Index count which should be 36
std::size_t CubeMesh::indexCount() const {
    return indices.size();
} 