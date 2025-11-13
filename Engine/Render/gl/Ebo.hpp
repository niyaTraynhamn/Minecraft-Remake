#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>    // std::size_t
#include <cstdint>    // std::uint32_t

#include <string>
#include <cmath>    
#include <vector> 

#include <iostream>


class EBO {
public: 
	// Reference ID of the EBO (Vertex Buffer Array)
	GLuint ID;
    // Constructor that builds the EBO 
	EBO(const std::vector<std::uint32_t>& indices, GLenum usage = GL_STATIC_DRAW);~EBO();
	// Binds the EBO 
	void Bind() const;
    // Unbinds the EBO
    void Unbind() const;
	// Deletes the EBO
	void Delete();
};

#endif