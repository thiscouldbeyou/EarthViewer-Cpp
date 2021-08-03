#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "EVSystem.hpp"
#include "Scene/Space/Skybox.hpp"
#include "Scene/Planet/Planet.hpp"
#include "Resourses/Shaders/Implimentations/PlanetShader.hpp"
#include "Resourses/Shaders/Implimentations/SkyboxShader.hpp"
#include "Scene/Camera/OrbitalCamera/OrbitalCamera.hpp"

class Renderer
{
private:
public:
    static auto RenderStartupScreen() -> void;
    static auto RenderPlanet(Planet &planet, Ref<PlanetShader> shader, OrbitalCamera &camera) -> void;
    static auto RenderSkybox(Skybox &skybox, Ref<SkyboxShader> shader, OrbitalCamera &camera) -> void;
    static auto RenderUI() -> void;
};

#endif
