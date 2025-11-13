#include "Vao.hpp"


//Creating the Vertex Array Object and a deconstuctor to delete the VAO
VAO::VAO() {
    glGenVertexArrays(1, &ID); //VAO (Vertex Array Object) → n = number of VAOs needed → ID (remembers vertex attribute state).
}
VAO::~VAO() {
    glDeleteVertexArrays(1, &ID); // Use the correct member variable name
}

//Linking the VBO to our VAO
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponets, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponets, type, GL_FALSE, static_cast<GLsizei>(stride), offset); //Tells OpenGL how to interpret the data inside the bound VBO.
    glEnableVertexAttribArray(layout); //Activates attribute index 0 (so the GPU will actually use it when feeding data into the vertex shader).
    VBO.Unbind();
}

// Binds the VAO 
void VAO::Bind() const{
    glBindVertexArray(ID); //Makes this VAO the “active” one. Everything you do with VBOs/EBOs + vertexAttribute setup will now be recorded inside this VAO.
}

// Unbinds the VAO
void VAO::Unbind() const {
    glBindVertexArray(0); //Unbinds the VAO so you don’t accidentally modify it later. The VAO still remembers: Which VBOs were bound
}

// Gets the ids
GLuint VAO::getID() const { 
    return ID; //Returning the ID of the VAO
}

// Deletes the VAO
void VAO::Delete() {
    glDeleteVertexArrays(1, &ID); //Deleting the Vertex Arrays
}