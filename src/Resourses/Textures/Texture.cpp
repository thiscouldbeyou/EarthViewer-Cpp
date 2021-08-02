#include "Texture.hpp"

#include <GL/glew.h>

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

auto TextureManager::LoadTexture2D(StringView name, StringView path) -> Ref<const Texture2D>
{
    printf("\t- Loading %s Texture: \'%s\'\n", name, path);

    stbi_set_flip_vertically_on_load(1);

    int width, height, channels;
    auto data = (unsigned char *)stbi_load(path, &width, &height, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load image with filepath %s\n", path);
        exit(1);
        return GetTexture(GameTextures2D::DEBUG_TEXTURE);
    }

    const TextureHandle textureHandle =
        SetupTexture(GL_REPEAT, GL_LINEAR, data, width, height, channels);

    stbi_image_free(data);

    return std::make_shared<const Texture2D>(textureHandle, width, height, channels);
}

auto TextureManager::LoadTexture2D(StringView name, const ByteSequence data,
                                   Size width, Size height, Size channels) -> Ref<const Texture2D>
{
    printf("\t- Loading %s(Internal)\n", name);

    const TextureHandle textureHandle =
        SetupTexture(GL_REPEAT, GL_LINEAR, data, width, height, channels);

    return std::make_shared<const Texture2D>(textureHandle, width, height, channels);
}

auto TextureManager::LoadTextureCubemap(StringView name, StringView path) -> Ref<const Texture>
{
    printf("\t- Loading Cubemap %s Texture: \'%s\'\n", name, path);
    return NULL;
}

auto TextureManager::SetTexture(GameTextures2D id, Ref<const Texture2D> data) -> void
{
    s2DTextures[(Size)id] = data;
}

auto TextureManager::Initialize() -> void
{
    static const ByteSequence debug_texture = {0xFF, 0x00, 0xFF, 0xFF,
                                               0x00, 0x00, 0x00, 0xFF,
                                               0xFF, 0x00, 0xFF, 0xFF,
                                               0x00, 0x00, 0x00, 0xFF};
    puts("Loading Textures");
    SetTexture(GameTextures2D::DEBUG_TEXTURE, LoadTexture2D("Debug", debug_texture, 2, 2, 4));
    SetTexture(GameTextures2D::STONE_TEXTURE, LoadTexture2D("Stone", "res/textures/stone.png"));
}