#include "shaderClass.hpp"


// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile){

    //Calling the function to load in the shaders
    std::string vShaderCode = FileLoading::loadShaderSource(vertexFile);
    std::string fShaderCode = FileLoading::loadShaderSource(fragmentFile);

    const char* vertexShaderSource = vShaderCode.c_str(); 
    const char* fragmentShaderSource = fShaderCode.c_str();

    //Creating a new shader object in GPU memory, gives back an intergr ID (refernce). Usiing  GLuint, OpenGL's version of an unassigned integer.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //We use the glCreateShader() to get a refernce value.
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); //Attaches GLSL source code (from .vert, .frag file) to shader object.
    glCompileShader(vertexShader); //Compiles the human-readable GLSL source into GPU machine code.
    compileErrors(vertexShader, "VERTEX"); //Running our errors program

    //We do the exact same thing for the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader); //To compile it now into machine code
    compileErrors(fragmentShader, "FRAGMENT"); //Running our errors program

    //To use the shaders we create a new program object in GPU memory and return its ID. A program is a container that can link multiple shaders together.
    ID = glCreateProgram(); //Creates a new shader object in GPU memory, gives back an integer ID (refernce).
    glAttachShader(ID, vertexShader);  //Attaches your GLSL source code (from your .vert or .frag file) to that shader object
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID); //Links all the attached shaders into one executable “shader program.” 
    //compileErrors(ID, "SHADER PROGRAM");
    compileErrors(ID, "PROGRAM");


    //Delete the standalone shader objects, as once they’re linked to the program, the program has its own copy.
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
}

// Sets a boolean uniform
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), (int)value);
    (glGetUniformLocation(ID, name.c_str()), (int)value);
}

// Sets a float uniform
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), (int)value);
}

// Sets an integer uniform
void Shader::setVec3(const std::string& name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

// Activates the Shader Program
void Shader::Activate() {
    glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete() {
    glDeleteProgram(ID);
}

// Compiles errors for the Shader Program
void Shader::compileErrors(unsigned int object, const char* type) {
    GLint success;
    GLchar infoLog[1024];

    std::string t(type);
    if (t == "VERTEX" || t == "FRAGMENT" || t == "GEOMETRY") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "SHADER_COMPILATION_ERROR of type: " << t << "\n"
                      << infoLog << std::endl;
        }
    } else if (t == "PROGRAM") {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "SHADER_LINKING_ERROR of type: " << t << "\n"
                      << infoLog << std::endl;
        }
    }
}
