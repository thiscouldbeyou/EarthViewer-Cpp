#ifndef SKYBOX_SHADER_HPP
#define SKYBOX_SHADER_HPP

#include "Resourses/Shaders/Shader.hpp"

class SkyboxShader : public Shader
{
private:
    auto LoadShaderProgram(const std::string &) const -> ShaderProgramHandle;

public:
    ShaderUniformLocation mModelLoc{};
    ShaderUniformLocation mViewLoc{};
    ShaderUniformLocation mProjLoc{};

    ShaderUniformLocation mAlbetoSamplerLoc{};

    SkyboxShader();
};

#endif