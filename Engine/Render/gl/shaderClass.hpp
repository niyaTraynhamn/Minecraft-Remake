#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Util\FileLoading.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>    
#include <iostream>


//Creating our function to load in the files this is private as it is not specified in public so it is only able to be accessed by this class.
// std::string loadShaderSource(const std::string& filepath);

class Shader {
    public:
        // Reference ID of the Shader Program
        GLuint ID;
        // Constructor that build the Shader Program from 2 different shaders
        Shader(const std::string& vertexFile, const std::string& fragmentFile);

        // Sets a boolean uniform
        void setBool(const std::string& name, bool value) const;

        // Sets a float uniform
        void setFloat(const std::string& name, float value) const;

        // Sets an integer uniform
        void setVec3(const std::string& name, const glm::vec3 &value);

        // Activates the Shader Program
        void Activate();
        // Deletes the Shader Program
        void Delete();
    private:
        void compileErrors(unsigned int shader, const char* type); //Creating a method to compile errors if our shaders fail
};

#endif 
