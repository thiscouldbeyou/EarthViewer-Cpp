#ifndef __SCENE__
#define __SCENE__

#include "EVSystem.hpp"
#include "Events/Event.hpp"

class Scene
{
private:
public:
    virtual auto Attach() -> void = 0;
    virtual auto Detach() -> void = 0;

    virtual auto HandleEvent(Event &) -> void = 0;
    virtual auto Update(Timestep) -> void = 0;
    virtual auto Render() -> void = 0;
};

#endif