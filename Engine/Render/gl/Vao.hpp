#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "Vbo.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

//This will be our VAO class this will create the vertex buffer obeject we will use
class VAO {
    public:
        // Reference ID of the VAO (Veretx Array Object)
        GLuint ID;
        // Constructor that builds the VAO and a deconstructor to delete the VAO
        VAO();~VAO();
        //Links the attribute ponter to the VAO
        void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponets, GLenum type, GLsizeiptr stride, void* offset);
        // Binds the VAO 
        void Bind() const;
        // Unbinds the VAO
        void Unbind() const;
        // Deletes the VAO
        void Delete();
        //gets the ids
        GLuint getID() const;

};

#endif