#ifndef __PLANET_SHADER__
#define __PLANET_SHADER__

#include "Resourses/Shaders/Shader.hpp"

class PlanetShader : public Shader
{
private:
    auto LoadShaderProgram(const std::string &) const -> ShaderProgramHandle;

public:
    ShaderUniformLocation mModelLoc{};
    ShaderUniformLocation mViewLoc{};
    ShaderUniformLocation mProjLoc{};

    ShaderUniformLocation mCameraPositionLoc{};
    ShaderUniformLocation mPlanetLoc{};

    PlanetShader();
};

#endif
