#pragma once



namespace unirender
{
    class CameraObject
    {
    public:
        void SetPerspective(float nearPlane, float farPlane, float top, float right);
        const ucc::Matrix4x4f& GetProjectionMatrix() const;
    private:
        ucc::Matrix4x4f 
    };
}