#include "rendercomponent.h"
#include "entity/entity.h"
#include "engine/gamecore/components/transformcomponent.h"

namespace unigamecore
{
    void RenderComponent::OnSerialize(ucc::ISerializer& serializer)
    {
        Component::OnSerialize(serializer);
		// serializer.Serialize("Position", m_Transform.GetPosition());
		// serializer.Serialize("Scale", m_Transform.GetScale());
		// serializer.Serialize("Rotation", m_Transform.GetRotation().GetAsVector());
    }

    void RenderComponent::Update()
    {
        TransformComponent* tc = GetOwner()->GetTransform();
        m_RenderInstance->SetModelTransform(tc->ToGlobalMatrix());
    }
}