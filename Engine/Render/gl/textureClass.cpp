#include"textureClass.hpp"

//Texture constructor, it loads and creates a texture from a file
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

    type = texType; // Assigns the type of the texture ot the texture object
    int widthImg, heightImg, numColCh; // Stores the width, height, and the number of color channels of the image

    stbi_set_flip_vertically_on_load(true);  // This is to make it so the image load the correct way vertically*
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
    if (!bytes) { std::cerr << "stbi: " << stbi_failure_reason() << "\n"; } //Checking for error

    glGenTextures(1, &ID); // Generates an OpenGL texture object
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Checking if the format of the image and cheking if its RGBA or RGB
    GLenum fmt = (numColCh == 4) ? GL_RGBA : GL_RGB;        // <-- don’t force RGBA if image is RGB
    glTexImage2D(texType, 0, fmt, widthImg, heightImg, 0, fmt, pixelType, bytes);  // Assigns the image to the OpenGL Texture object
    glGenerateMipmap(texType); // Generates MipMaps

    stbi_image_free(bytes); // Deletes the image data as it is already in the OpenGL Texture object
    glBindTexture(texType, 0); // Unbinds the OpenGL Texture object so that it can't accidentally be modified

}

// Assigns a texture unit to a texture
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    // Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

// Binds a texture
void Texture::Bind() {
    glBindTexture(type, ID);
}

// Unbinds a texture
void Texture::Unbind() {
    glBindTexture(type, 0);
}

//Getting the texture ID
GLuint Texture::getID() const { 
    return ID; 
}

// Deletes a texture
void Texture::Delete() {
    glDeleteTextures(1, &ID);
}