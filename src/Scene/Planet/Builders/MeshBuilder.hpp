#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP

#include <array>
#include <cstdint>
#include <glm/glm.hpp>

#include "Mesh/Mesh.hpp"

#define FACE_SIDE_LENGTH 32
#define VERT_SIDE_LENGTH (FACE_SIDE_LENGTH + 1)

struct VertexData
{
    glm::vec3 mPositions{};
    glm::vec2 mTextureCoords{};
};

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

using PlanetFaceVertices = std::array<std::array<VertexData, VERT_SIDE_LENGTH>, VERT_SIDE_LENGTH>;
using PlanetFaceIndicies = std::array<std::array<PlanetFace, FACE_SIDE_LENGTH>, FACE_SIDE_LENGTH>;

class PlanetMesh : public Mesh
{
private:
public:
    PlanetMesh(VertexArrayObjectHandle handle, Size length)
        : Mesh(handle, length)
    {
    }
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