#ifndef __SHADER__HPP__
#define __SHADER__HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "EVSystem.hpp"
#include "Utilities/ResourseLoader.hpp"

using ShaderProgramHandle = unsigned int;
using ShaderHandle = unsigned int;
using ShaderUniformLocation = int;

struct Shader
{
private:
protected:
    const ShaderProgramHandle mProgramHandle{};

    auto LoadShader(GLenum, const std::string &) const -> ShaderHandle;
    auto ValidateShaderProgram(ShaderProgramHandle) const -> void;

public:
    Shader(ShaderProgramHandle);

    auto Start() const -> void;
    auto Stop() const -> void;

    auto GetUniformLocation(const std::string &name) const -> ShaderUniformLocation;
    auto LoadInt(ShaderUniformLocation, int) const -> void;
    auto LoadFloat(ShaderUniformLocation, float) const -> void;
    auto LoadFloat2(ShaderUniformLocation, const glm::vec2 &) const -> void;
    auto LoadFloat3(ShaderUniformLocation, const glm::vec3 &) const -> void;
    auto LoadFloat4(ShaderUniformLocation, const glm::vec4 &) const -> void;
    auto LoadMatrix4(ShaderUniformLocation, const glm::mat4 &) const -> void;

    auto GetShaderProgramHandle() const { return mProgramHandle; };
};

#endif