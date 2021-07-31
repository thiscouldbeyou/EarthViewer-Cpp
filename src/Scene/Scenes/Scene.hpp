#ifndef __SCENE__
#define __SCENE__

#include "EVSystem.hpp"

class Scene
{
private:
public:
    virtual auto Attach()  -> void = 0;
    virtual auto Detach()  -> void= 0;

    virtual auto Update(Timestep)  -> void= 0;
    virtual auto Render()  -> void= 0;
};

#endif