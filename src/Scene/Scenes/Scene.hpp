#ifndef SCENE_HPP
#define SCENE_HPP

#include "EVSystem.hpp"
#include "Events/Event.hpp"

class Scene
{
private:
public:
    Scene() = default;
    virtual ~Scene(){}

    virtual auto Attach() -> void = 0;
    virtual auto Detach() -> void = 0;

    virtual auto HandleEvent(Event &) -> void = 0;
    virtual auto Update(Timestep) -> void = 0;
    virtual auto Render() -> void = 0;
};

#endif