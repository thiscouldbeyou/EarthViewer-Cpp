#ifndef __RENDERER__
#define __RENDERER__

#include "EVSystem.hpp"
#include "Scene/Planet/Planet.hpp"
#include "Scene/Camera/FreeCamera/FreeCamera.hpp"
#include "Resourses/Shaders/Implimentations/PlanetShader.hpp"

class Renderer
{
private:
public:
    auto RenderPlanet(Planet &, Ref<PlanetShader>, FreeCamera) -> void;
    auto RenderSkybox() -> void;
    auto RenderUI() -> void;
};

#endif
