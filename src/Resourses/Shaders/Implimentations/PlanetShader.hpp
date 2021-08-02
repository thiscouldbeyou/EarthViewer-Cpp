#ifndef PLANET_SHADER_HPP
#define PLANET_SHADER_HPP

#include "Resourses/Shaders/Shader.hpp"

class PlanetShader : public Shader
{
private:
    auto LoadShaderProgram(const std::string &) const -> ShaderProgramHandle;

public:
    ShaderUniformLocation mModelLoc{};
    ShaderUniformLocation mViewLoc{};
    ShaderUniformLocation mProjLoc{};

    ShaderUniformLocation mReverseModelLoc{};

    ShaderUniformLocation mCameraPositionLoc{};
    ShaderUniformLocation mPlanetLoc{};

    PlanetShader();
};

#endif
