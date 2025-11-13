#include "Vbo.hpp"

//Constructor and Deconstructor to build and delete the VBO
VBO::VBO(const std::vector<Vertex>& vertices, GLenum usage) {
    glGenBuffers(1, &ID); //VBO → Vertex Buffer Object ID (stores actual vertex data).
    glBindBuffer(GL_ARRAY_BUFFER, ID); //Binds the VBO to the GL_ARRAY_BUFFER target (meaning it’s being used for vertex attributes).
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), usage); //Copies your vertex array (vertices) from CPU memory into GPU memory. GL_STATIC_DRAW tells OpenGL you don’t plan to change this data often.
}
VBO::~VBO() {
    glDeleteBuffers(1, &ID); // Use the correct member variable name
}

// Binds the VBO 
void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID); //Binds the VBO to the GL_ARRAY_BUFFER target (meaning it’s being used for vertex attributes).
}

// Unbinds the VBO
void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0); //We basically just unbind both the VBO and VAO by binding to zero
}

//Deletes the VBO
void VBO::Delete() {
    glDeleteBuffers(1, &ID); //Deleting the Buffers
}
