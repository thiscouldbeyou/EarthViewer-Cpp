#include "SkyboxShader.hpp"

auto SkyboxShader::LoadShaderProgram(const std::string &filename) const -> ShaderProgramHandle
{
    printf("Loading Shader Program %s\n", filename.c_str());
    auto vs = LoadShader(GL_VERTEX_SHADER, filename);
    auto fs = LoadShader(GL_FRAGMENT_SHADER, filename);

    auto program = (ShaderProgramHandle)glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glBindAttribLocation(mProgramHandle, 0, "aPosition");

    glLinkProgram(program);
    ValidateShaderProgram(program);
    
    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

SkyboxShader::SkyboxShader()
    : Shader(LoadShaderProgram("SkyboxShader"))
{
    mModelLoc = GetUniformLocation("uModelMatrix");
    mViewLoc = GetUniformLocation("uViewMatrix");
    mProjLoc = GetUniformLocation("uProjMatrix");

    mAlbetoSamplerLoc = GetUniformLocation("mAlbetoSampler");
}