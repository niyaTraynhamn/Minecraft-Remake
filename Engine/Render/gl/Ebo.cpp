#include "Ebo.hpp"

//Creating the constructor for our Element array buffer object
EBO::EBO(const std::vector<std::uint32_t>& indices, GLenum usage) {
    glGenBuffers(1, &ID); //VBO → Vertex Buffer Object ID (stores actual vertex data).
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //Binds the VBO to the GL_ARRAY_BUFFER target (meaning it’s being used for vertex attributes).
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint32_t)), indices.data(), usage); //Copies your vertex array (vertices) from CPU memory into GPU memory. GL_STATIC_DRAW tells OpenGL you don’t plan to change this data often.
}

//Deconstructor to delete the Element array buffer object
EBO::~EBO() {
    glDeleteBuffers(1, &ID); // Use the correct member variable name
}

// Binds the EBO 
void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //Binds the VBO to the GL_ARRAY_BUFFER target (meaning it’s being used for vertex attributes).
}

// Unbinds the EBO
void EBO::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //We basically just unbind both the VBO and VAO by binding to zero
}

//Deletes the EBO
void EBO::Delete() {
    glDeleteBuffers(1, &ID); //Deleting the Buffers
}