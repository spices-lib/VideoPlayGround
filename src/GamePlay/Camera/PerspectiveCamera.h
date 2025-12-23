#pragma once
#include "Core/Core.h"
#include "Camera.h"

namespace PlayGround {

    class PerspectiveCamera : public Camera
    {
    public:

        PerspectiveCamera();
        PerspectiveCamera(const PerspectiveParam& param);

        ~PerspectiveCamera() override = default;

        glm::mat4 GetPMatrix() override;

        PerspectiveParam& GetParam() { return m_PerspectiveParam; }

        const PerspectiveParam& GetParam() const { return m_PerspectiveParam; }

    private:

        void CalculatePMatrixReverseZ() override;

    private:

        PerspectiveParam m_PerspectiveParam;
    };
}