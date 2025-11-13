#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include"C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>    
#include <iostream>


class Camera {
public:
    glm::vec3 Position; //Setting the camera position
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); //Setting the camera direction to -1 on the Z axis
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //Setting the camera Up direction to 1 on the Y axis
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    // This is for our camera height base
    const float kFloorY   = 0.0f;   // base ground plane
    const float kEyeHeight = 1.7f;  // camera height above the ground (tweak to taste)

    // Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
    // Stores the width and height of the window
    int width;
    int height;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.1f;
    float sensitivity = 100.0f;

    float deltaTime = 0.0f;  // Time between current and last frame
    float lastFrame = 0.0f;  // Time of last frame

    // Camera constructor to set up initial values
    Camera(int width, int height, glm::vec3 position);

    // Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(GLuint program, const char* uniform);

    // Handles camera inputs
	void Inputs(GLFWwindow* window);


};

#endif