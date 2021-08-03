#include "Texture.hpp"

#include <GL/glew.h>
#include <cstring>

#include "stb_image/stb_image.h"

TextureArray2D TextureManager::s2DTextures;
TextureArrayCubemap TextureManager::sCubemapTextures;

auto TextureManager::SetupTexture(Size wrap, Size filter, const unsigned char data[],
                                  Size width, Size height, Size channels) -> TextureHandle
{
    TextureHandle textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    const auto channelSetting = GL_RGB + channels - 3;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channelSetting,
                 GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureHandle;
}

auto TextureManager::Initialize() -> void
{
    static const ByteSequence debug_texture = {0xFF, 0x00, 0xFF, 0xFF,
                                               0x00, 0x00, 0x00, 0xFF,
                                               0xFF, 0x00, 0xFF, 0xFF,
                                               0x00, 0x00, 0x00, 0xFF};
    puts("Loading Textures");
    SetTexture(AppTextures2D::DEBUG_TEXTURE, LoadTexture2D("Debug", debug_texture, 2, 2, 4));
    SetTexture(AppTextures2D::STONE_TEXTURE, LoadTexture2D("Stone", "res/textures/stone.png"));
    SetTexture(AppTexturesCubemap::GALAXY_CUBEMAP, LoadTextureCubemap("Galaxy", "res/textures/skybox/panorama"));
}

auto TextureManager::LoadTexture2D(StringView name, StringView path) -> Ref<const Texture2D>
{
    printf("\t- Loading %s Standard Texture: \'%s\'\n", name, path);

    stbi_set_flip_vertically_on_load(1);

    int width, height, channels;
    auto data = (unsigned char *)stbi_load(path, &width, &height, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load image with filepath %s\n", path);
        exit(1);
        return GetTexture(AppTextures2D::DEBUG_TEXTURE);
    }

    const TextureHandle textureHandle =
        SetupTexture(GL_REPEAT, GL_NEAREST, data, width, height, channels);

    stbi_image_free(data);

    return std::make_shared<const Texture2D>(textureHandle, width, height, channels);
}

auto TextureManager::LoadTexture2D(StringView name, const ByteSequence data,
                                   Size width, Size height, Size channels) -> Ref<const Texture2D>
{
    printf("\t- Loading %s Standard Texture: (Internal)\n", name);

    const TextureHandle textureHandle =
        SetupTexture(GL_REPEAT, GL_LINEAR, data, width, height, channels);

    return std::make_shared<const Texture2D>(textureHandle, width, height, channels);
}

auto TextureManager::LoadTextureCubemap(StringView name, StringView path) -> Ref<const TextureCubemap>
{
    TextureHandle texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    Size path_length = strlen(path);
    Size fullpath_length = path_length + 7;
    assert(fullpath_length <= 64);
    char filepath[64];
    memset(filepath, '\0', sizeof(filepath));
    memcpy(filepath, path, path_length);
    filepath[path_length + 0] = '_';
    filepath[path_length + 1] = '0';
    filepath[path_length + 2] = '.';
    filepath[path_length + 3] = 'j';
    filepath[path_length + 4] = 'p';
    filepath[path_length + 5] = 'g';

    stbi_set_flip_vertically_on_load(0);
    for (Size i = 0; i < 6; i++)
    {
        filepath[path_length + 1] = '0' + i;
        printf("\t- Loading %s Cubemap Texture: \'%s\'\n", name, filepath);

        int width, height, nrChannels;
        auto data = stbi_load(filepath, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB + nrChannels - 3, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            fprintf(stderr, "Cubemap texture file not found %s\n", filepath);
            stbi_image_free(data);
            exit(1);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return std::make_shared<const TextureCubemap>(texture);
}

auto TextureManager::SetTexture(AppTextures2D id, Ref<const Texture2D> data) -> void
{
    s2DTextures[(Size)id] = data;
}

auto TextureManager::SetTexture(AppTexturesCubemap id, Ref<const TextureCubemap> data) -> void
{
    sCubemapTextures[(Size)id] = data;
}



auto TextureManager::GetTexture(AppTextures2D texture) -> Ref<const Texture2D>
{
    return s2DTextures[(Size)texture];
}

auto TextureManager::GetTexture(AppTexturesCubemap texture) -> Ref<const TextureCubemap>
{
    return sCubemapTextures[(Size)texture];
}