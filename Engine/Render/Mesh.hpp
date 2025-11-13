#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Vao.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\mesh_types.hpp"

#include <glm/glm.hpp> // Add this include for glm::vec3 and glm::vec2
#include <cstddef>    // std::size_t
#include <cstdint>    // std::uint32_t

#include <string>
#include <vector>   

#include <iostream>

//The job of this file is to create a generic CPU-side mesh: vertices/indices/vertex layout

//Enum to define the topology of the mesh
enum class MeshTopology {
    Triangles,   // GL_TRIANGLES
    Lines,       // GL_LINES
    LineStrip,   // GL_LINE_STRIP
    TriangleStrip, // GL_TRIANGLE_STRIP
    // Add more if needed
};

//An Axis-Aligned Bounding Box is the smallest box, aligned to the world axes, that fully contains your mesh. It’s defined by two points: min and max (component-wise).
// struct AABB {
//     glm::vec3 min; // e.g., {-0.5f, -0.5f, -0.5f}
//     glm::vec3 max; // e.g., { 0.5f,  0.5f,  0.5f}
// };


class Mesh {
    public:

        // Precomputed ranges for drawing subsets of the cube
        FaceRanges ranges{};

        // Constructor
        Mesh(std::vector<Vertex> vertices, std::vector<std::uint32_t> indices, MeshTopology topology);

        // Convenience getters we want to avoid storing duplicate of the counts we have
        std::size_t vertexCount() const; 
        std::size_t indexCount() const; 

        const std::vector<Vertex>& getVertices() const { return vertices;} //a function to get the vertices
        const std::vector<std::uint32_t>& getIndices() const { return indices; } //a function to get the indices
        //const AABB& bounding() const { return bounds; } //a function to get the bounds
        MeshTopology getTopology() const { return topology; } //a function to get the topology

        //Will come back and add as I dont know now must learn culling 
        // Compute the bounding box
        //void computebounding();
    
      
    private:
        //AABB bounds;
        MeshTopology topology;
        std::vector<Vertex> vertices;   // pos, normal, uv, color
        std::vector<std::uint32_t> indices;   // noting they’re in index units (not bytes)

};  

#endif
