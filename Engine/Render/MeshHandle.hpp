#ifndef MESHHANDLE_CLASS_H
#define MESHHANDLE_CLASS_H

#include "mesh.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\shaderClass.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Vao.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Vbo.hpp"
#include "C:\Users\Niyam\OneDrive\Documents\Desktop\Minecraft Game\Engine\Render\gl\Ebo.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>       // glm::mat4
 #include <cstddef> // Required for offsetof

#include <vector>
#include <cmath>    

#include <iostream>

/*Rendering/MeshHandle (GPU handle + metadata),
    The MeshHandle struct/class:
        Owns/holds: the VAO id (and, by association, the VBO/EBO bound to it).
        Stores: indexCount and the precomputed ranges from CubeMesh.
        A thin “descriptor” the renderer can consume in 1–2 lines.
Can either (a) own the VAO/VBO/EBO lifetimes (delete on destruction), or (b) reference objects you manage elsewhere—pick one 
policy and be consistent.*/

/* The job of the MeshHandle file and class if to:
    take CPU geometry (from CubeMesh) → upload to GPU (VAO/VBO/EBO) → keep GL ids + precomputed index ranges so renderers can draw 
subsets (sides/top/bottom) without knowing geometry details.*/

class MeshHandle {
public:

    //Takes CPU geometry (CubeMesh) and uploads it, we use explict as the CubeMesh holds data — it's not just a utility.
    explicit MeshHandle(const Mesh& objMesh);

    // Renderer calls this before glDrawElements
    void bind() const;

    // Query methods for the renderer
    GLsizei indexCount() const { return indexCount_; }
    const FaceRanges& ranges() const { return ranges_; }

    // Convenience: compute byte offset into EBO for a face’s first index
    // (so renderer can do glDrawElements(GL_TRIANGLES, face.count, GL_UNSIGNED_INT, offset))
    static const void* byteOffsetForIndexStart(std::uint32_t startIndex) {
        return reinterpret_cast<const void*>(static_cast<std::size_t>(startIndex) * sizeof(std::uint32_t));
    }

    GLuint getID() const;

private:
    //We are owning our VAO, VBO, EBO (your wrapper classes).
    VAO vao_;
    VBO vbo_;
    EBO ebo_;

    //Storing my indexcount and my face ranges
    GLsizei indexCount_{0};
    FaceRanges ranges_{}; //These are pointers to our cubemesh data
};

#endif
