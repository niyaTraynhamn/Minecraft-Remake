#include "Mesh.hpp"

//Building our mesh constructor
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<std::uint32_t> indices, MeshTopology topology) {
    this->vertices = vertices;
    this->indices = indices;
    this->topology = topology;
    // Compute the bounding box
    //bounding(); 
}

//Return our Vertex count which should be 24
std::size_t Mesh::vertexCount() const {
    return vertices.size();
} 

//Return our Index count which should be 36
std::size_t Mesh::indexCount() const {
    return indices.size();
} 
