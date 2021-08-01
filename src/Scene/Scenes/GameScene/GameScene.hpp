#ifndef __GAME_SCENE__
#define __GAME_SCENE__

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

    virtual auto HandleEvent(Event &) -> void override;
    virtual auto Update(Timestep) -> void override;
    virtual auto Render() -> void override;
};

#endif