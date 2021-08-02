#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>

#include "EVSystem.hpp"
#include "Utilities/StringView.hpp"

using TextureHandle = unsigned int;
using ByteSequence = unsigned char[];

class Texture
{
private:
    const TextureHandle mHandle{};

public:
    Texture() = default;
    Texture(TextureHandle handle)
        : mHandle(handle)
    {
    }

    auto GetTextureHandle() const { return mHandle; }
};

class Texture2D : public Texture
{
private:
    const Size mWidth{};
    const Size mHeight{};
    const Size mChannelCount{};

public:
    Texture2D() = default;
    Texture2D(TextureHandle handle, Size width, Size height, Size count)
        : Texture(handle), mWidth(width), mHeight(height), mChannelCount(count)
    {
    }

    auto GetWidth() const { return mWidth; }
    auto GetHeight() const { return mHeight; }
    auto GetChannelCount() const { return mChannelCount; }
};

enum class GameTextures2D : uint8_t
{
    STONE_TEXTURE,
    DEBUG_TEXTURE,
};

enum class GameTexturesCubemap : uint8_t
{
    GALAXY_CUBEMAP,
    DEBUG_CUBEMAP,
};

using TextureArray2D = std::array<Ref<const Texture2D>, (Size)GameTextures2D::DEBUG_TEXTURE + 1>;
using TextureArrayCubemap = std::array<Ref<const GameTexturesCubemap>, (Size)GameTexturesCubemap::DEBUG_CUBEMAP + 1>;

class TextureManager
{
private:
    static TextureArray2D s2DTextures;
    static TextureArrayCubemap sCubemapTextures;

    static auto SetupTexture(Size, Size, const unsigned char[], Size, Size, Size) -> TextureHandle;

    static auto LoadTexture2D(StringView, StringView) -> Ref<const Texture2D>;
    static auto LoadTexture2D(StringView, const ByteSequence, Size, Size, Size) -> Ref<const Texture2D>;
    static auto LoadTextureCubemap(StringView, StringView) -> Ref<const Texture>;

    static auto SetTexture(GameTextures2D, Ref<const Texture2D>) -> void;

public:
    static auto Initialize() -> void;

    static auto GetTexture(GameTextures2D texture) -> Ref<const Texture2D>;
};

#endif