#ifndef __RESOURSE_LOADER__HPP__
#define __RESOURSE_LOADER__HPP__

#include "EVSystem.hpp"
#include "Resourses/Textures/Texture.hpp"

class GLFWLoader
{
private:
public:
    static auto Initialize() -> bool;
};

class GLEWLoader
{
private:
public:
    static auto Initialize() -> bool;
};

class TextFileLoader
{
private:
public:
    static auto LoadFile(const std::string &filepath) -> const std::string;
};

class TextureLoader
{
private:
public:
    static auto LoadTexture(const std::string &filepath) -> Ref<Texture2D>;
};

#endif