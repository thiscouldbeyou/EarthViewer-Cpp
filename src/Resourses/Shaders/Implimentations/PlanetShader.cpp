#include "PlanetShader.hpp"

auto PlanetShader::LoadShaderProgram(const std::string &filename) const -> ShaderProgramHandle
{
    printf("Loading Shader Program %s\n", filename.c_str());
    auto vs = LoadShader(GL_VERTEX_SHADER, filename);
    auto cs = LoadShader(GL_TESS_CONTROL_SHADER, filename);
    auto es = LoadShader(GL_TESS_EVALUATION_SHADER, filename);
    auto fs = LoadShader(GL_FRAGMENT_SHADER, filename);

    auto program = (ShaderProgramHandle)glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, cs);
    glAttachShader(program, es);
    glAttachShader(program, fs);
    glLinkProgram(program);

    ValidateShaderProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, cs);
    glDetachShader(program, es);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(cs);
    glDeleteShader(es);
    glDeleteShader(fs);

    return program;
}

PlanetShader::PlanetShader()
    : Shader(LoadShaderProgram("PlanetShader"))
{
    mModelLoc = GetUniformLocation("uModelMatrix");
    mViewLoc = GetUniformLocation("uViewMatrix");
    mProjLoc = GetUniformLocation("uProjMatrix");

    mCameraPositionLoc = GetUniformLocation("uCameraPosition");
    //mPlanetLoc = GetUniformLocation("uPlanetPosition");
}