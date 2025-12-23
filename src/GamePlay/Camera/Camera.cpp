#include "Camera.h"
#include "PerspectiveCamera.h"

namespace PlayGround {

    SP<Camera> Camera::CreatePerspective(const PerspectiveParam& param)
    {
        return CreateSP<PerspectiveCamera>(param);
    }

    const glm::mat4& Camera::GetPMatrixReverseZ()
    {
        CalculatePMatrixReverseZ();
        return m_ProjectionMatrix;
    }
}
