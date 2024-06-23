#pragma once
#include "core/coreheader.h"

namespace unirender
{
    class CameraObject
    {
    public:
        inline const ucc::Matrix4x4f& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const ucc::Matrix4x4f& GetViewMatrix() const { return m_ViewMatrix; }

        void SetPerspective(float nearPlane, float farPlane, float top, float right);
        void SetPerspectiveFov(float tanAngle, float aspectRatio, float nearPlane, float farPlane);

        inline const ucc::Vector4f& GetViewPosition() { return m_ViewPosition; }
        inline const ucc::Quaternion4f& GetViewRotation() { return m_ViewRotation; }
        void CameraObject::SetViewPosition(const ucc::Vector4f& pos);
        void CameraObject::SetViewRotation(const ucc::Quaternion4f& rot);

        float m_Pitch = 0.0f;
        float m_Roll = 0.0f;
        float m_Yaw = 0.0f;

    private:
        ucc::Matrix4x4f m_ProjectionMatrix;
        ucc::Matrix4x4f m_ViewMatrix;

        ucc::Vector4f m_ViewPosition = ucc::Vector4f(0.0f, 0.0f, -5.0f, 1.0f);
        ucc::Quaternion4f m_ViewRotation;
        void UpdateViewMatrix();
    };
}
