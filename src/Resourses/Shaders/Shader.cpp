#include "Shader.hpp"

static auto GetShaderExtention(GLenum type)
{
    static const std::string ext = ".glsl";
    if (type == GL_VERTEX_SHADER)
        return "/vs" + ext;
    if (type == GL_TESS_CONTROL_SHADER)
        return "/cs" + ext;
    if (type == GL_TESS_EVALUATION_SHADER)
        return "/es" + ext;
    if (type == GL_GEOMETRY_SHADER)
        return "/gs" + ext;
    if (type == GL_FRAGMENT_SHADER)
        return "/fs" + ext;
    return std::string("");
}

auto Shader::LoadShader(GLenum type,
                        const std::string &filename) const -> ShaderHandle
{
    // integrate std::filepaths
    static const auto SHADER_FOLDER = std::string("res/shaders/");
    const auto filewithext = filename + GetShaderExtention(type);
    const auto filepath = SHADER_FOLDER + filewithext;
    printf("\t- Loading %s...", filewithext.c_str());

    const auto src = TextFileLoader::LoadFile(filepath);
    const auto csrc = src.c_str();
    if (csrc)
        puts("Success!");
    else
        puts("Failed!");

    auto shader = (ShaderHandle)glCreateShader(type);
    glShaderSource(shader, 1, &csrc, NULL);
    glCompileShader(shader);

    auto result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        auto infoLogLength = -1;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Compiling %d:\n%s\n", type, infoLog);
    }

    return shader;
}

auto Shader::ValidateShaderProgram(ShaderProgramHandle program) const -> void
{
    auto result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        auto infoLogLength = -1;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Linking:\n%s\n", infoLog);
    }
}

Shader::Shader(ShaderProgramHandle handle)
    : mProgramHandle(handle)
{
}

auto Shader::Start() const -> void
{
    glUseProgram(mProgramHandle);
}

auto Shader::Stop() const -> void
{
    glUseProgram(0);
}

auto Shader::GetUniformLocation(const std::string &name) const -> ShaderUniformLocation
{
    glGetUniformLocation(mProgramHandle, name.c_str());
}

auto Shader::LoadInt(ShaderUniformLocation loc, int value) const -> void
{
    glUniform1i((GLint)loc, (GLint)value);
}

auto Shader::LoadFloat(ShaderUniformLocation loc, float value) const -> void
{
    glUniform1f((GLint)loc, (GLfloat)value);
}

auto Shader::LoadFloat2(ShaderUniformLocation loc, const glm::vec2 &value) const -> void
{
    glUniform2f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y);
}

auto Shader::LoadFloat3(ShaderUniformLocation loc, const glm::vec3 &value) const -> void
{
    glUniform3f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z);
}

auto Shader::LoadFloat4(ShaderUniformLocation loc, const glm::vec4 &value) const -> void
{
    glUniform4f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z, (GLfloat)value.w);
}

auto Shader::LoadMatrix4(ShaderUniformLocation loc, const glm::mat4 &value) const -> void
{
    glUniformMatrix4fv((GLint)loc, 1, GL_FALSE, (GLfloat *)&value[0][0]);
}