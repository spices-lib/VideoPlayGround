#include "Transform.h"

namespace PlayGround {

    glm::mat4 Transform::ToMatrix() const
    {
        return
            glm::translate(glm::mat4(1.0f), position) *
            GetRotationMatrix(rotation) *
            glm::scale(glm::mat4(1.0f), scale);
    }

    glm::mat4 Transform::GetRotationMatrix(const glm::vec3& rotation)
    {
        return
            glm::toMat4(
            glm::quat({
                glm::radians(rotation.x),
                glm::radians(rotation.y),
                glm::radians(rotation.z)
            })
            );
    }

    glm::mat4 Transform::ToMatrix(const Transform& transform)
    {
        return
            glm::translate(glm::mat4(1.0f), transform.position) *
            GetRotationMatrix(transform.rotation) *
            glm::scale(glm::mat4(1.0f), transform.scale);
    }
}