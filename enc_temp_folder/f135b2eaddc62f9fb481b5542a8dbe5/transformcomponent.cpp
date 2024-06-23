#include "transformcomponent.h"

namespace unigamecore
{
    void TransformComponent::OnSerialize(ucc::ISerializer& serializer)
    {
        Component::OnSerialize(serializer);
        serializer.Serialize("Position", m_Transform.GetPosition());
        serializer.Serialize("Scale", m_Transform.GetScale());
        serializer.Serialize("Rotation", m_Transform.GetRotation().GetAsVector());
    }

    void TransformComponent::Update()
    {

    }

    ucc::Matrix4x4f TransformComponent::ToLocalMatrix() const
    { 
        return m_Transform.ToMatrix(); 
    }
}