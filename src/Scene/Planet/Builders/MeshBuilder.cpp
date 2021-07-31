#include "MeshBuilder.hpp"

#include "cstring"
#include <GL/glew.h>
#include "Utilities/GeneralMath.hpp"

PlanetMesh::~PlanetMesh()
{
    glDeleteVertexArrays(1, &mHandle);
}

void PlanetMesh::Bind()
{
    glBindVertexArray(mHandle);
}

void PlanetMesh::Unbind()
{
    glBindVertexArray(0);
}

static void GenerateFaceBuffer(PlanetFaceVertices &verticies)
{
    static const auto dTHETA = 90.0f / (VERT_SIDE_LENGTH - 1);
    static const auto OFFSET = 45.0f;
    for (Size v = 0; v < VERT_SIDE_LENGTH; v++)
    {
        const auto vTheta = v * dTHETA - OFFSET;
        const auto vcos = (float)cos(glm::radians(vTheta));
        const auto vsin = (float)sin(glm::radians(vTheta));
        for (Size u = 0; u < VERT_SIDE_LENGTH; u++)
        {
            const auto uTheta = u * dTHETA - OFFSET;
            const auto ucos = (float)cos(glm::radians(uTheta));
            const auto usin = (float)sin(glm::radians(uTheta));
            verticies[v][u] = glm::vec3(usin / ucos, vsin / vcos, 1);
        }
    }
}

void MeshBuilder::GenerateVertexPositions() const
{
    static const std::array<glm::mat4, 6> TRANSFORM_LOOKUPS = {
        gm::Rotate(0, -90, 0),
        gm::Rotate(0, 90, 0),
        gm::Rotate(90, 0, 0),
        gm::Rotate(-90, 0, 0),
        gm::Rotate(0, 0, 0),
        gm::Rotate(0, 180, 0),
    };

    PlanetFaceVertices buffer;
    GenerateFaceBuffer(buffer);

    for (auto f = 0; f < 6; f++)
    {
        glm::mat4 transform = TRANSFORM_LOOKUPS[f];
        auto &verticies = mVerticies->data()[f];
        for (auto v = 0; v < verticies.size(); v++)
            for (auto u = 0; u < verticies[v].size(); u++)
            {
                const auto &point = buffer[v][u];
                const auto trans = transform * glm::vec4(point, 1);
                verticies[v][u] = glm::vec3(trans.x, trans.y, trans.z);
            }
    }
}

void MeshBuilder::GenerateVertexIndicies() const
{
    static const auto STRIDE = VERT_SIDE_LENGTH * VERT_SIDE_LENGTH;

    for (auto f = 0; f < 6; f++)
    {
        auto &faces = mFaces->data()[f];
        for (auto v = 0; v < faces.size(); v++)
        {
            for (auto u = 0; u < faces[v].size(); u++)
            {
                const auto index = v * VERT_SIDE_LENGTH + u;
                const auto offset = STRIDE * f;

                const auto p0 = (Indice)(offset + index);
                const auto p1 = (Indice)(offset + index + 1);
                const auto p2 = (Indice)(offset + index + VERT_SIDE_LENGTH + 1);
                const auto p3 = (Indice)(offset + index + VERT_SIDE_LENGTH);

                //faces[v][u] = {p0, p3, p1, p1, p3, p2};
                faces[v][u] = PlanetFace(p0, p1, p2, p3);
            }
        }
    }
}

void MeshBuilder::GeneratePlanetMeshData() const
{
    GenerateVertexPositions();
    GenerateVertexIndicies();
}

Ref<PlanetMesh> MeshBuilder::GeneratePlanetVAO() const
{
    const auto verticies = mVerticies->data();
    const auto faces = mFaces->data();

    VertexArrayObjectHandle vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBufferObjectHandle vertexPositionBuffer;
    glGenBuffers(1, &vertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(std::array<PlanetFaceVertices, 6>),
                 verticies,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);

    VertexBufferObjectHandle vertexIndiciesBuffer;
    glGenBuffers(1, &vertexIndiciesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndiciesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(std::array<PlanetFaceIndicies, 6>),
                 faces,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);

    return std::make_shared<PlanetMesh>(vao, sizeof(std::array<PlanetFaceIndicies, 6>) / sizeof(Indice));
}

Ref<PlanetMesh> MeshBuilder::GeneratePlanetMesh() const
{
    GeneratePlanetMeshData();
    return GeneratePlanetVAO();
}

MeshBuilder::MeshBuilder()
    : mVerticies(std::make_unique<std::array<PlanetFaceVertices, 6>>()),
      mFaces(std::make_unique<std::array<PlanetFaceIndicies, 6>>())
{
}