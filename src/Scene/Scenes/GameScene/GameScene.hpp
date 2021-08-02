#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Render/Renderer.hpp"
#include "Scene/Scenes/Scene.hpp"
#include "Scene/Planet/Planet.hpp"
#include "Scene/Camera/OrbitalCamera/OrbitalCamera.hpp"

class GameScene : public Scene
{
private:
    Renderer mRenderer;

    Planet mPlanet;
    //FreeCamera mFreeCamera;
    OrbitalCamera mOrbitalCamera;

    Ref<PlanetShader> mPlanetShader;

public:
    GameScene();
    ~GameScene();

    virtual auto Attach() -> void override;
    virtual auto Detach() -> void override;

    virtual auto HandleEvent(Event &event) -> void override;
    virtual auto Update(Timestep timestep) -> void override;
    virtual auto Render() -> void override;
};

#endif