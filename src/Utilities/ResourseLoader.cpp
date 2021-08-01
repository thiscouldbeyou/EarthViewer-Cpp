#include "ResourseLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

auto GLFWLoader::Initialize() -> bool
{
    static bool initialized = false;
    printf("Initializing GLFW...");
    if (initialized)
    {
        puts("Success!");
        return true;
    }

    if (!glfwInit())
    {
        puts("Failed!");
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    initialized = true;
    puts("Success!");
    return true;
}

auto GLEWLoader::Initialize() -> bool
{
    static bool initialized = false;
    printf("Initializing GLEW...");
    if (initialized)
    {
        puts("Success!");
        return true;
    }

    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        puts("Failed!");
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    initialized = true;
    puts("Success!");
    return true;
}

auto GLEWLoader::SetPatchVertices(int count) -> void
{
    int MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	printf("Max number of patch vertices: %d\n", MaxPatchVertices);
	glPatchParameteri(GL_PATCH_VERTICES, count);
    printf("Set number of patch vertices: %d\n", count);
}

auto TextFileLoader::LoadFile(const std::string &filepath) -> const std::string
{
    auto file = fopen(filepath.c_str(), "rt");
    if (!file)
        fprintf(stderr, "Could not open file: %s", filepath.c_str());
    fseek(file, 0, SEEK_END);
    auto length = ftell(file);
    auto data = (char *)malloc(sizeof(char) * (length + 1));
    memset(data, 0, length + 1);
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);

    auto result = std::string(data);
    free(data);
    return result;
}

auto TextureLoader::LoadTexture(const std::string &filename) -> Ref<Texture2D>
{
    static const auto prefix_path = std::string("res/textures/");
    const auto fullpath = prefix_path + filename;
    printf("Loading Texture %s\n", filename.c_str());

    GLuint textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);

    int width, height, channels;
    auto data = stbi_load(fullpath.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load image with filepath %s\n", fullpath.c_str());
        return nullptr;
    }

    auto format = GL_RGBA;

    const auto channelSetting = GL_RGB + channels - 3;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, channelSetting,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return std::make_shared<Texture2D>(textureHandle, width, height, channelSetting);
}
