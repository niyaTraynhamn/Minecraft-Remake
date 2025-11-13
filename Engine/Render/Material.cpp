#include "Material.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

// Pull real definitions only in the .cpp to keep headers light
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\MeshHandle.hpp"     // adjust path to your MeshHandle
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"  // Shader            
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\textureClass.hpp" // Texture

//Creating the material bind and draw functions
void BlockMaterial::bind(const BlockState& block, const DrawCtx& ctx) const {
    if (!shader || !side || !surface) return;

    shader->Activate();  // <-- move to the top

    // per-object
    const GLint modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ctx.model));

    // tint (grass/leaves)
    if (block.type == BlockType::Grass || block.type == BlockType::Leaves) {
        shader->setBool("uUseTint", true);
        shader->setVec3("uTintColor", glm::vec3(0.62f, 0.78f, 0.36f));
    } else {
        shader->setBool("uUseTint", false);
    }
}


//This will be the draw function for our block material
void BlockMaterial::draw(const MeshHandle& mesh) const {
    if (!side || !surface) return;

    // Activate openGl textures
    glActiveTexture(GL_TEXTURE0);

    // Bind and draw the side texture
    side->Bind();
    glDrawElements(GL_TRIANGLES, sidesCount, GL_UNSIGNED_INT, (void*)(0));

    // Top + Bottom: next 12 indices (offset = 24 * sizeof(GLuint))
    surface->Bind();
    const GLsizei offsetBytes = static_cast<GLsizei>(sizeof(GLuint) * topBottomOffsetIdx);
    glDrawElements(GL_TRIANGLES, topBottomCount, GL_UNSIGNED_INT, (void*)(offsetBytes));

}


// ---------------- LightMaterial ----------------

void lightMaterial::bind(const BlockState& block, const DrawCtx& ctx) const {
    if (!shader) return;
    
    shader->Activate();

    // model
    const GLint modelLoc = glGetUniformLocation(shader->ID, "model"); //retrieving the location (an integer handle) of a uniform variable within the shader program.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ctx.model)); //uploading a 4×4 matrix (or an array of matrices) to a uniform variable in the shader program.

    // lightColor (match name AND type: vec4)
    const GLint colorLoc = glGetUniformLocation(shader->ID, "lightColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(lightColor));

}

void lightMaterial::draw(const MeshHandle& mesh) const {
    // Single draw across the whole index buffer
    mesh.bind();//bind the mesh VAO
    glDrawElements(GL_TRIANGLES, mesh.indexCount(), GL_UNSIGNED_INT, (void*)0);
}




