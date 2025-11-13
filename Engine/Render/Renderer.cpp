#include "Renderer.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>       // glm::mat4

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>    
#include <iostream>

// Drawing the block to the window
void Renderer::draw(const IMaterial& mat, const BlockState& block, const glm::mat4& model) const {
        glBindVertexArray(mesh_->getID());
        DrawCtx ctx{ model };
        mat.bind(block, ctx);
        mat.draw(*mesh_);
        glBindVertexArray(0);
}


// void Renderer::draw(const BlockState& block, const glm::mat4& model) const {
//     if (!mat_->shader || !mat_->side || !mat_->surface) return;

//     //if the block is grass, set the tint uniforms
//     if (block.type == BlockType::Grass) {
//         mat_->shader->setBool("uUseTint", true);
//         mat_->shader->setVec3("uTintColor", glm::vec3(0.62f, 0.78f, 0.36f)); // example green
//     } 
//     else {
//         mat_->shader->setBool("uUseTint", false);
//     }

//     // Use shader
//     mat_->shader->Activate();

//     // set model
//     const GLint modelLoc = glGetUniformLocation(mat_->shader->ID, "model");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
//     auto id = mesh_->getID();    
//     glBindVertexArray(id); //binding the vertex array

//     // Sides: first 24 indices
//     glActiveTexture(GL_TEXTURE0);
//     mat_->side->Bind();
//     glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)(0));

//     // Top + Bottom: next 12 indices (offset = 24 * sizeof(GLuint))
//     mat_->surface->Bind();
//     glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * 24));
//     glBindVertexArray(0);
// }