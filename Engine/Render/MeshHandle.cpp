#include "meshHandle.hpp"

#include <iostream>

#include <cstddef> // offsetof

MeshHandle::MeshHandle(const Mesh& objMesh)
: vao_(),
  vbo_(objMesh.getVertices()),         // pass the vectors (see VBO/EBO ctors)
  ebo_(objMesh.getIndices()),
  indexCount_(static_cast<GLsizei>(objMesh.getIndices().size()))
{
    vao_.Bind();
    vbo_.Bind();
    ebo_.Bind();

    const GLsizei stride = static_cast<GLsizei>(sizeof(Vertex));

    // pos (0), normal (1), color (2), uv (3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);

    vao_.Unbind();
    vbo_.Unbind();
    ebo_.Unbind();
}

void MeshHandle::bind() const {
    vao_.Bind();
}

GLuint MeshHandle::getID() const { 
    return vao_.getID(); 
}