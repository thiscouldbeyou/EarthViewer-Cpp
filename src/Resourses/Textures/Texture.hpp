#ifndef __TEXTURE__HPP__
#define __TEXTURE__HPP__

using TextureHandle = unsigned int;

class Texture2D
{
private:
    TextureHandle mHandle {};
    int mWidth {};
    int mHeight {};
    int mChannelCount {};

public:
    Texture2D(TextureHandle handle, int width, int height, int count)
        : mHandle(handle), mWidth(width), mHeight(height), mChannelCount(count)
    {
    }

    auto GetTextureHandle() const { return mHandle; }
    auto GetWidth() const { return mWidth; }
    auto GetHeight() const { return mHeight; }
    auto GetChannelCount() const { return mChannelCount; }
};

#endif