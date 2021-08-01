#ifndef __RENDERER__
#define __RENDERER__

#include "EVSystem.hpp"
#include "Scene/Planet/Planet.hpp"
#include "Scene/Camera/OrbitalCamera/OrbitalCamera.hpp"
#include "Resourses/Shaders/Implimentations/PlanetShader.hpp"

class Renderer
{
private:
public:
    auto RenderPlanet(Planet &, Ref<PlanetShader>, OrbitalCamera &) -> void;
    auto RenderSkybox() -> void;
    auto RenderUI() -> void;
};

#endif
