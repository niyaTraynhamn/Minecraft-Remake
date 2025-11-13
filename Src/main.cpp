#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <iostream>

#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Vao.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Vbo.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Ebo.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\textureClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\camera.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Game\World\TerrainGen.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Game\Models\CubeMesh.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\Mesh.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\MeshHandle.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\blockStateData.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\mesh_types.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\Material.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\Renderer.hpp"



//-------------------------------- Lighting code --------------------------------

//We will make a small cube to represent the light source

// 8 corners (±0.1f)
std::vector<Vertex> lightvertices = {   
    // Front (+Z)
    {{-0.5f, -0.5f,  0.5f}, {0,0,1}, {1,1,1}, {0,0}},
    {{ 0.5f, -0.5f,  0.5f}, {0,0,1}, {1,1,1}, {1,0}},
    {{ 0.5f,  0.5f,  0.5f}, {0,0,1}, {1,1,1}, {1,1}},
    {{-0.5f,  0.5f,  0.5f}, {0,0,1}, {1,1,1}, {0,1}},

    // Back (−Z)
    {{ 0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {0,0}},
    {{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {1,0}},
    {{-0.5f,  0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {1,1}},
    {{ 0.5f,  0.5f, -0.5f}, {0,0,-1}, {1,1,1}, {0,1}},

    // Left (−X)
    {{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {1,1,1}, {0,0}},
    {{-0.5f, -0.5f,  0.5f}, {-1,0,0}, {1,1,1}, {1,0}},
    {{-0.5f,  0.5f,  0.5f}, {-1,0,0}, {1,1,1}, {1,1}},
    {{-0.5f,  0.5f, -0.5f}, {-1,0,0}, {1,1,1}, {0,1}},

    // Right (+X)
    {{ 0.5f, -0.5f,  0.5f}, { 1,0,0}, {1,1,1}, {0,0}},
    {{ 0.5f, -0.5f, -0.5f}, { 1,0,0}, {1,1,1}, {1,0}},
    {{ 0.5f,  0.5f, -0.5f}, { 1,0,0}, {1,1,1}, {1,1}},
    {{ 0.5f,  0.5f,  0.5f}, { 1,0,0}, {1,1,1}, {0,1}},

    // Top (+Y)
    {{-0.5f,  0.5f,  0.5f}, {0,1,0}, {1,1,1}, {0,0}},
    {{ 0.5f,  0.5f,  0.5f}, {0,1,0}, {1,1,1}, {1,0}},
    {{ 0.5f,  0.5f, -0.5f}, {0,1,0}, {1,1,1}, {1,1}},
    {{-0.5f,  0.5f, -0.5f}, {0,1,0}, {1,1,1}, {0,1}},

    // Bottom (−Y)
    {{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,1,1}, {0,0}},
    {{ 0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,1,1}, {1,0}},
    {{ 0.5f, -0.5f,  0.5f}, {0,-1,0}, {1,1,1}, {1,1}},
    {{-0.5f, -0.5f,  0.5f}, {0,-1,0}, {1,1,1}, {0,1}},
};

std::vector<std::uint32_t> lightindices = {
    0,1,2,  0,2,3,      // bottom (Y-)
    0,4,7,  0,7,3,      // front (Z+)
    3,7,6,  3,6,2,      // right (X+)
    2,6,5,  2,5,1,      // back (Z-)
    1,5,4,  1,4,0,      // left (X-)
    4,5,6,  4,6,7       // top (Y+)
};


//-------------------------------- WINDOW --------------------------------

const unsigned int width = 1280; //This is the width of the window
const unsigned int height = 720; //This is the height of the window


int main() {
    
    //-------------------------------- INITIALIZE GLFW --------------------------------
    
    //Initalizing the program using glfwInit(); you can also just call it without the edge case.
    if (!glfwInit()) { 
        std::cerr << "GLFW init failed\n"; 
        return -1; 
    }

    //We need to specify what version of OpenGL we are using as glfw dosent really the version.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //This is done by calling the WindowHints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //We need to specify the Major, Minor, and version number)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //The last hint we have to give is which openGL pofile we want to use.
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    //-------------------------------- CREATING WINDOW --------------------------------
    
    
    //Now we must call the window, We call the datatype of the window object in GFLW.
    GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft Game Remake", nullptr, nullptr); //The CreateWinodw() function takes 5 params: width, hieght, name, fullscren (Y/N), and the last thing is not important so (NULL)
    //Adding a fail safe/error checking to see if the window is loading properlly.
    if (window == nullptr){
        std::cerr << "Window ro create GFLW window. \n"; 
        glfwTerminate(); 
        return -1;
    }

    glfwMakeContextCurrent(window); //We must tell the program GLFW since we have created the window we now want to use it.

    //We use Glad to add color to the window --> gladLoadGL();
    if (!gladLoadGL()) { 
        std::cerr << "Glad/OpenGL  failed\n"; 
        return -1; 
    }
    //Then we tell OpenGL the viewport of our window, which is just the area of the window we want openGL to render in
    glViewport(0, 0, width, height); //From bottom left corner of the window (0,0) to the top right corner of the window  (800,800)

    
    //-------------------------------- MAKING BLOCK & GETTING SHADERS --------------------------------

    // Part 1 of blocks creating the call of the cubemesh
    CubeMesh cubeCPU = CubeMesh::makeUnitCube();
    Mesh cubeMesh(cubeCPU.vertices, cubeCPU.indices, MeshTopology::Triangles); //Upload cubemesh to the GPU through the mesh from the cubemesh
    MeshHandle cubeHandle(cubeMesh); //Creating the mesh handle from the mesh

    Mesh lightMesh(lightvertices, lightindices, MeshTopology::Triangles);
    MeshHandle lightHandle(lightMesh);


    // Part 2 of blocks and lighting creating the shaders, generates shader object using shaders texture.vert and texture.frag
    Shader shaderProgram("C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Shaders/Core/basic.vert", "C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Shaders/Core/basic.frag");
    Shader lightShaderProgram("C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Shaders/Core/light.vert", "C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Shaders/Core/light.frag");

    
    //-------------------------------- CREATING LIGHT CUBE --------------------------------

    glm::vec3 lightPos = glm::vec3(0.5f, 1.5f, 0.5f); //Setting the position of the light cube
    glm::mat4 lightModel = glm::mat4(1.0f); //Creating the model matrix for the light cube
    lightModel = glm::translate(lightModel, lightPos); //Translating the light cube to its position

    //-------------------------------- CREATING TEXTURES --------------------------------

    //Creating the textures
    Texture sideTex_grass("C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Textures/Blocks/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture surfaceTex_grass("C:/Users/Niyam/OneDrive/Documents/Desktop/Minecraft Game/Assets/Textures/Blocks/grass_block_top.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //Activating the shader programs
    shaderProgram.Activate();
    lightShaderProgram.Activate(); //We want tell OpenGL which Shader Program we want to use'

    //Assigning the texture to the shader
    sideTex_grass.texUnit(shaderProgram, "texSide", 0);
    surfaceTex_grass.texUnit(shaderProgram, "texTop", 1);

    // every frame before drawing blocks:
    glActiveTexture(GL_TEXTURE0);
    sideTex_grass.Bind();
    glActiveTexture(GL_TEXTURE1);
    surfaceTex_grass.Bind();

    // Example BlockState (however you define it)
    BlockState grass(BlockType::Grass, /*solid*/true, /*transparent*/false);
    BlockState light(BlockType::Light, /*solid*/true, /*transparent*/false); // Placeholder for light block state if needed
    
    //Building the material, grassMat.sidesCount/topBottomCount/topBottomOffsetIdx already default to 24/12/24
    BlockMaterial grassMat;
    grassMat.shader   = &shaderProgram;
    grassMat.side     = &sideTex_grass;
    grassMat.surface  = &surfaceTex_grass;

    lightMaterial lightMat;
    lightMat.shader = &lightShaderProgram;
    lightMat.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // White light color


    //Creating the renderers
    Renderer blockR(cubeHandle); // Pass by value or reference if Renderer expects Mesh and Material, not pointers
    Renderer lightR(lightHandle); // can reuse the same VAO; light VS only reads location 0

    //-------------------------------- ENABLING DEPTH TESTING AND CAMERA DEFINING --------------------------------

	glEnable(GL_DEPTH_TEST); //Enabling the depth must be called

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f)); //Calling our camera class creating the width, the height, and setting the position of the camera

    //-------------------------------- CREATING TERRAIN --------------------------------

    auto floorModels = Terrain::makeFlatGrid(10, 10, 0.0f);  //Creating our terrian
    

    //-------------------------------- WHILE LOOP (GAME LOOP) --------------------------------

    //We now must create a while loop which will only end on the condition that the window should close
    while (!glfwWindowShouldClose(window)) {

        //-------------------------------- DRAW --------------------------------

        //Now we want OpenGL to execute the command we have just told it to prepare for.
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //We are coloring the screen blue the last number ALPHA is set to 1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and depth buffer

        //Actiavting our shaderprogram and drawing the triangle shape  
		shaderProgram.Activate(); //We want tell OpenGL which Shader Program we want to use'
        
        //-------------------------------- CAMERA --------------------------------
  
        // Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
        camera.Position.y = std::max(camera.Position.y, camera.kFloorY + camera.kEyeHeight);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram.ID, "camMatrix");
		camera.Matrix(lightShaderProgram.ID, "camMatrix");

        //-------------------------------- DRAW --------------------------------

        for (const auto& m : floorModels) {
            blockR.draw(grassMat, grass, m);  // or grass block state if you have it const IMaterial& mat, const BlockState& block, const glm::mat4& model
        }

        // Drawing the light cube
        lightShaderProgram.Activate(); //We want tell OpenGL which Shader Program we want to use'
        lightR.draw(lightMat, light, lightModel); // can reuse the same VAO; light VS only reads location 0
    
        //-------------------------------- UPDATE --------------------------------
       
        //So in order to see the buffers as we have a front buffer with the color we want and the back we want to swap buffers.
        glfwSwapBuffers(window);
        glfwPollEvents(); //We need to tell GLFW to process all the events such as the window appearing, being resized, ect.
    }

    //-------------------------------- CLEANING & DELETING --------------------------------

    // Delete all the objects we've created
    sideTex_grass.Delete();
	shaderProgram.Delete();
    
    glfwDestroyWindow(window);  //Once we are done with the window itself we want to delete it
    glfwTerminate(); //Terminating the program
    
    return 0;
 
}
