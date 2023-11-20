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

        inline const ucc::Vector4f& GetViewPosition() { return m_ViewPosition; }
        inline const ucc::Quaternion4f& GetViewRotation() { return m_ViewRotation; }
        void CameraObject::SetViewPosition(const ucc::Vector4f& pos);
        void CameraObject::SetViewRotation(const ucc::Quaternion4f& rot);

    private:
        ucc::Matrix4x4f m_ProjectionMatrix;
        ucc::Matrix4x4f m_ViewMatrix;

        ucc::Vector4f m_ViewPosition;
        ucc::Quaternion4f m_ViewRotation;
        void UpdateViewMatrix();
    };
}