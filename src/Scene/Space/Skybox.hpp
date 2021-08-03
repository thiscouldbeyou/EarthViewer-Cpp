#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <glm/glm.hpp>
#include "Mesh/Mesh.hpp"

struct SkyboxMesh : public Mesh
{
private:
public:
    SkyboxMesh() = default;
    SkyboxMesh(VertexArrayObjectHandle handle, Size length)
        : Mesh(handle, length)
    {
    }
};

class Skybox
{
private:
    glm::vec3 mRotation{};
    Ref<SkyboxMesh> mMesh{};

    auto GenerateSkyboxMesh() -> Ref<SkyboxMesh>;
public:
    Skybox();

    auto Rotate(float rx, float ry, float rz) -> void;
    auto GenerateModelMatrix() -> glm::mat4;

    auto GetMesh() const -> Ref<SkyboxMesh> { return mMesh; }
};

#endif