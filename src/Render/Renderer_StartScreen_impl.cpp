#include "Renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Display/Display.hpp"
#include "Resourses/Textures/Texture.hpp"
#include "stb_image/stb_image.h"

static TextureHandle LoadTexture()
{
    const char *path = "res/textures/icon.png";
    int width, height, channels;
    auto data = (unsigned char *)stbi_load(path, &width, &height, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load image with filepath %s\n", path);
        exit(1);
    }

    TextureHandle textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const auto channelSetting = GL_RGB + channels - 3;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channelSetting,
                 GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return textureHandle;
}

static ShaderProgramHandle CreateShader()
{
    static const char *vs_src = R"VS(
        #version 330 core

        in vec3 aPosition;
        in vec2 aTexCoords;

        out vec2 vTexCoords;

        uniform mat4 uModel = mat4(1.0);
        uniform mat4 uProj = mat4(1.0);

        void main(){
            gl_Position = uProj * uModel * vec4(aPosition, 1);
            vTexCoords = aTexCoords;
        }
        
    )VS";

    static const char *fs_src = R"FS(
        #version 330 core

        in vec2 vTexCoords;

        out vec4 FragColor;

        uniform sampler2D mTextureSampler;

        void main(){
            vec4 color = texture2D(mTextureSampler, vTexCoords);
            if(color.a < 0.5) discard;
            FragColor = color;
        }

    )FS";

    auto vs = (ShaderHandle)glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_src, NULL);
    glCompileShader(vs);

    auto result = GL_FALSE;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        auto infoLogLength = -1;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetShaderInfoLog(vs, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Compiling %d:\n%s\n", 0, infoLog);
    }

    auto fs = (ShaderHandle)glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_src, NULL);
    glCompileShader(fs);

    result = GL_FALSE;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        auto infoLogLength = -1;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetShaderInfoLog(fs, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Compiling %d:\n%s\n", 1, infoLog);
    }

    auto program = (ShaderProgramHandle)glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    //glBindAttribLocation(program, 0, "aPosition");
    //glBindAttribLocation(program, 1, "aTexCoords");

    glLinkProgram(program);

    result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        auto infoLogLength = -1;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Linking:\n%s\n", infoLog);
        exit(1);
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

static VertexArrayObjectHandle CreateVAO()
{
    struct Vertex
    {
        glm::vec3 mPosition;
        glm::vec2 mTexCoords;
    };

    static const Vertex VERTICES[] = {
        Vertex{glm::vec3(-1, 1, 0), glm::vec2(0, 0)},
        Vertex{glm::vec3(-1, -1, 0), glm::vec2(0, 1)},
        Vertex{glm::vec3(1, 1, 0), glm::vec2(1, 0)},

        Vertex{glm::vec3(1, 1, 0), glm::vec2(1, 0)},
        Vertex{glm::vec3(-1, -1, 0), glm::vec2(0, 1)},
        Vertex{glm::vec3(1, -1, 0), glm::vec2(1, 1)}};

    auto program = CreateShader();

    VertexArrayObjectHandle vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBufferObjectHandle vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)12);

    return vao;
}

auto Renderer::RenderStartupScreen() -> void
{
    auto &display = DisplayManager::GetDisplay();

    auto texture = TextureManager::LoadTexture2D("Start Screen", "res/textures/icon.png");

    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(display.GetWindowHandle());

    auto program = CreateShader();
    auto vao = CreateVAO();
    glUseProgram(program);

    //glUniform
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(120, 120, 1));
    glUniformMatrix4fv(glGetUniformLocation(program, "uModel"), 1, GL_FALSE, &transform[0][0]);
    auto s = display.GetSize();
    glm::mat4 proj = glm::ortho(-s.mWidth * 0.5f, s.mWidth * 0.5f, -s.mHeight * 0.5f, s.mHeight * 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &proj[0][0]);
    glUniform1d(glGetUniformLocation(program, "mTextureSampler"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glPointSize(12);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);

    glfwSwapBuffers(display.GetWindowHandle());
}