#pragma once
#include "Core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PlayGround {

    struct Transform
    {
        glm::vec3 position{ 0.0f };
        glm::vec3 rotation{ 0.0f };
        glm::vec3 scale   { 1.0f };

        glm::mat4 ToMatrix() const;

        static glm::mat4 GetRotationMatrix(const glm::vec3& rotation);
        static glm::mat4 ToMatrix(const Transform& transform);
    };
}