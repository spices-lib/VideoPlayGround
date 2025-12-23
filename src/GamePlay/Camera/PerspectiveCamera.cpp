#include "PerspectiveCamera.h"
#include "Core/Math/Math.h"

namespace PlayGround {

    PerspectiveCamera::PerspectiveCamera()
        : Camera(ProjectionType::Perspective)
    {}

    PerspectiveCamera::PerspectiveCamera(const PerspectiveParam& param)
        : Camera(ProjectionType::Perspective)
        , m_PerspectiveParam(param)
    {}

    glm::mat4 PerspectiveCamera::GetPMatrix()
    {
        return PerspectiveMatrix(
                m_PerspectiveParam.fov        ,
                m_PerspectiveParam.nearPlane  ,
                100000000.0f,
                m_PerspectiveParam.aspectRatio
        );
    }

    void PerspectiveCamera::CalculatePMatrixReverseZ()
    {
        m_ProjectionMatrix = PerspectiveMatrixInverseZ(
                m_PerspectiveParam.fov        ,
                m_PerspectiveParam.nearPlane  ,
                m_PerspectiveParam.aspectRatio
        );
    }
}
