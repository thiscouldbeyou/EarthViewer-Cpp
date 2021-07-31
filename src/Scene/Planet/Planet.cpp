#include "Planet.hpp"

#include "Utilities/GeneralMath.hpp"

Planet::Planet()
    : mMeshBuilder(),
      mPosition(0, 0, 0),
      mRotation(0, 0, 0),
      mMesh(mMeshBuilder.GeneratePlanetMesh())
{
}

Planet::~Planet()
{
}

auto Planet::Update(Timestep timestep) -> void
{
}

auto Planet::GenerateModelMatrix() -> glm::mat4 {
  const auto translation = glm::translate(glm::mat4(1.0f), mPosition);
  const auto rotation = gm::Rotate(mRotation);
  return translation * rotation;
}