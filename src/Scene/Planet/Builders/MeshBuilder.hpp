#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP

#include <array>
#include <cstdint>
#include <glm/glm.hpp>

#include "EVSystem.hpp"

#define FACE_SIDE_LENGTH 32
#define VERT_SIDE_LENGTH (FACE_SIDE_LENGTH + 1)

using VertexArrayObjectHandle = unsigned int;
using VertexBufferObjectHandle = unsigned int;
using Indice = uint32_t;

struct PlanetFace
{
    Indice i00, i01, i02, i03;
    //Indice i10, i11, i12;

    PlanetFace() = default;
    PlanetFace(Indice p0, Indice p1, Indice p2, Indice p3)
        : i00(p0), i01(p1), i02(p2), i03(p3)
    {
    }
    
};

using PlanetFaceVertices = std::array<std::array<glm::vec3, VERT_SIDE_LENGTH>, VERT_SIDE_LENGTH>;
using PlanetFaceIndicies = std::array<std::array<PlanetFace, FACE_SIDE_LENGTH>, FACE_SIDE_LENGTH>;

struct PlanetMesh
{
    VertexArrayObjectHandle mHandle{};
    Size mLength{};

    PlanetMesh(VertexArrayObjectHandle handle, Size length)
        : mHandle(handle),
          mLength(length)
    {
    }
    ~PlanetMesh();

    void Bind();
    void Unbind();
};

class MeshBuilder
{
private:
    Scope<std::array<PlanetFaceVertices, 6>> mVerticies{};
    Scope<std::array<PlanetFaceIndicies, 6>> mFaces{};

    void GenerateVertexPositions() const;
    void GenerateVertexIndicies() const;
    void GeneratePlanetMeshData() const;
    Ref<PlanetMesh> GeneratePlanetVAO() const;

public:
    MeshBuilder();

    Ref<PlanetMesh> GeneratePlanetMesh() const;
};

#endif