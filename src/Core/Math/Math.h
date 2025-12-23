#pragma once
#include "Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PlayGround {

    bool DecomposeTransform(
            const glm::mat4& transform,
            glm::vec3&       outTranslation,
            glm::vec3&       outRotation,
            glm::vec3&       outScale
    );

    glm::mat4 PerspectiveMatrix(float fov, float nearPlane, float farPlane, float aspectRatio);
    glm::mat4 OrthographicMatrix(float left, float right, float top, float bottom, float nearPlane, float farPlane);
    glm::mat4 PerspectiveMatrixInverseZ(float fov, float nearPlane, float aspectRatio);
}