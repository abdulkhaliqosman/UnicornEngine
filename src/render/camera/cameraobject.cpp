#include "cameraobject.h"

namespace unirender
{
    void CameraObject::SetPerspective(float nearPlane, float farPlane, float top, float right)
    {
        m_ProjectionMatrix = ucc::Matrix4x4f::Zero();
        m_ProjectionMatrix[0].SetX(nearPlane / right);
        m_ProjectionMatrix[1].SetY(nearPlane / top);
        m_ProjectionMatrix[2].SetZ((farPlane + nearPlane) / (farPlane - nearPlane));

        // m_ProjectionMatrix[2].SetW(-(2.0f * farPlane * nearPlane) / (farPlane - nearPlane));
        // m_ProjectionMatrix[3].SetZ(-1.0f);

        m_ProjectionMatrix[2].SetW(-1.0f);
        m_ProjectionMatrix[3].SetZ(-(2.0f * farPlane * nearPlane) / (farPlane - nearPlane));

    }

    void CameraObject::SetViewPosition(const ucc::Vector4f& pos)
    { 
        m_ViewPosition = pos;
        UpdateViewMatrix();
    }

    void CameraObject::SetViewRotation(const ucc::Quaternion4f& rot)
    { 
        m_ViewRotation = rot;
        UpdateViewMatrix();
    }

    void CameraObject::UpdateViewMatrix()
    {

    }
}