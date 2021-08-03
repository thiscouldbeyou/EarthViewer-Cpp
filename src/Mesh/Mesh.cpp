#include "Mesh.hpp"

#include "GL/glew.h"

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mHandle);
}

auto Mesh::Bind()-> void
{
    glBindVertexArray(mHandle);
}

auto Mesh::Unbind() -> void
{
    glBindVertexArray(0);
}
