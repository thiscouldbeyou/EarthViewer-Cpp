#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "EVSystem.hpp"
#include "Scene/Planet/Planet.hpp"
#include "Scene/Camera/OrbitalCamera/OrbitalCamera.hpp"
#include "Resourses/Shaders/Implimentations/PlanetShader.hpp"

class Renderer
{
private:
public:
    auto RenderPlanet(Planet &planet, Ref<PlanetShader> shader, OrbitalCamera &camera) -> void;
    auto RenderSkybox() -> void;
    auto RenderUI() -> void;
};

#endif
