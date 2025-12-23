#pragma once
#include "Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PlayGround {

    enum class ProjectionType
    {
        Perspective  = 0,
        Orthographic = 1,
    };

    struct OrthographicParam
    {
        float left      = -10.0f; 
        float right     = 10.0f;  
        float top       = 10.0f;  
        float bottom    = -10.0f; 
        float nearPlane = 0.01f;  
        float farPlane  = 1000.0f;
    };

    struct PerspectiveParam
    {
        float fov           = 45.0f;
        float nearPlane     = 0.01f; 
        float aspectRatio   = 1.777f;
    };

    class Camera
    {
    public:

        static SP<Camera> CreatePerspective(const PerspectiveParam& param);

    public:

        Camera() = default;

        Camera(ProjectionType type)
            : m_ProjectionType(type)
        {}

        virtual ~Camera() = default;

        const glm::mat4& GetPMatrixReverseZ();

        virtual glm::mat4 GetPMatrix() = 0;

        const ProjectionType& GetProjectionType() const { return m_ProjectionType; }

    private:

        virtual void CalculatePMatrixReverseZ() = 0;

    protected:

        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

        ProjectionType m_ProjectionType = ProjectionType::Perspective;
    };
}