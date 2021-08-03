#ifndef MESH_HPP
#define MESH_HPP

#include "EVSystem.hpp"

using VertexArrayObjectHandle = unsigned int;
using VertexBufferObjectHandle = unsigned int;
using Indice = uint32_t;

class Mesh
{
private:
    VertexArrayObjectHandle mHandle{};
    Size mLength{};

public:
    Mesh() = default;
    Mesh(VertexArrayObjectHandle handle, Size length)
        : mHandle(handle), mLength(length)
    {
    }
    ~Mesh();

    auto Bind() -> void;
    auto Unbind() -> void;

    auto GetLength() const -> Size { return mLength; };
};

#endif