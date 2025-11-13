#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include"shaderClass.hpp"

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<stb/stb_image.h>

#include <string>
#include <cmath>    
#include <iostream>

class Texture {
public:
    GLuint ID; // This is a call to our objects that are used in the Shader class
    GLenum type; // Type is a public member variable of the Texture class, and it's of type GLenum, which is an OpenGL-defined type—essentially an unsigned integer used to represent various constants in OpenGL.

    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType); //Creating a constructor to intalize our objects

    // Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Gets textureID
	GLuint getID() const;
	// Deletes a texture
	void Delete();

};

#endif 