#ifndef __PLANET__HPP__
#define __PLANET__HPP__

#include "Builders/MeshBuilder.hpp"
#include "Resourses/Shaders/Implimentations/PlanetShader.hpp"

class Planet
{
private:
    MeshBuilder mMeshBuilder{};

    glm::vec3 mPosition{};
    glm::vec3 mRotation{};

    Ref<PlanetMesh> mMesh{}; 

public:
    Planet();
    ~Planet();

    auto Update(Timestep) ->  void;

    auto GenerateModelMatrix() -> glm::mat4;

    auto GetPosition() const -> const glm::vec3 & { return mPosition; }
    auto GetRotation() const -> const glm::vec3 & { return mRotation; }
    auto GetMesh() -> Ref<PlanetMesh> { return mMesh; }
};

#endif