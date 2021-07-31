#ifndef __FREE_CAMERA__HPP__
#define __FREE_CAMERA__HPP__

#include <glm/glm.hpp>
#include "../Camera.hpp"

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

class FreeCamera : public Camera
{
private:
    glm::vec3 mPosition{};
    glm::vec3 mRotation{};

    CameraSettings mSettings{};

    glm::mat4 mViewMatrix{};
    glm::mat4 mProjMatrix{};

public:
    FreeCamera(float, float, float,
               float = 0, float = 0, float = 0,
               float = 70, float = 1, float = 0.01, float = 1000);

    auto Move(float, float, float) -> glm::vec3 &;
    auto Rotate(float, float, float) -> glm::vec3 &;
    auto SetPosition(float, float, float) -> glm::vec3 &;
    auto SetRotation(float, float, float) -> glm::vec3 &;

    auto UpdateViewMatrix() -> glm::mat4 &;
    auto UpdateProjMatrix() -> glm::mat4 &;

    auto GetPosition() const -> const glm::vec3 & { return mPosition; }
    auto GetRotation() const -> const glm::vec3 & { return mRotation; }
    auto GetViewMatrix() const -> const glm::mat4 & { return mViewMatrix; }
    auto GetProjMatrix() const -> const glm::mat4 & { return mProjMatrix; }
};

#endif