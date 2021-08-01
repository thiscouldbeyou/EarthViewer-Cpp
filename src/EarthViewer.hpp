#ifndef __EARTH_VIEWER__HPP__
#define __EARTH_VIEWER__HPP__

#include "EVSystem.hpp"
#include "Display/Display.hpp"
#include "Scene/SceneManager.hpp"
#include "Events/Event.hpp"

class EarthViewer
{
private:
    SceneManager mSceneManager{};

public:
    EarthViewer();
    ~EarthViewer();

    auto HandleEvent(Event &) -> void;
    auto Update(Timestep) -> void;
    auto Render() -> void;
};

#endif