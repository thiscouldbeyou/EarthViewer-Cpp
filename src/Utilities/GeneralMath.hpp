#ifndef __GENERAL_MATH__
#define __GENERAL_MATH__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gm{
    auto Rotate(float, float, float) -> glm::mat4;
    auto Rotate(const glm::vec3 &) -> glm::mat4;
}

#endif