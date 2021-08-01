#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

struct CameraSettings
{
    float mFOV{};
    float mAspect{};
    float mNear{};
    float mFar{};

    CameraSettings() = default;
    CameraSettings(float fov, float aspect, float near, float far)
        : mFOV(fov),
          mAspect(aspect),
          mNear(near),
          mFar(far)
    {
    }
};

class Camera {
    private:
    public:
};

#endif