#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "mesh_types.hpp"

#include <glm/glm.hpp> // Add this include for glm::vec3 and glm::vec2
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>    // std::size_t
#include <cstdint>    // std::uint32_t

#include <string>
#include <vector> 
#include <cmath>    

#include <iostream>


class VBO {
public: 
	// Reference ID of the VBO (Element Buffer Object)
	GLuint ID;
    // Constructor that builds the VBO 
	VBO(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);~VBO();

	// Binds the VBO 
	void Bind() const;
    // Unbinds the VBO
    void Unbind() const;
	// Deletes the VBO
	void Delete();
};

#endif