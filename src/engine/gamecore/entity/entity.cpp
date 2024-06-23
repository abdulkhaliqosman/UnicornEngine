#include "entity.h"
#include "component/component.h"
#include "components/transformcomponent.h"

namespace unigamecore
{
    void Entity::Startup()
    {

    }

    void Entity::Update()
    {
        for (Component* component : m_Components)
        {
            component->Update();
        }
    }

    void Entity::AddTransform(TransformComponent* tc)
    {
        m_Transform = tc;
        AddComponent(tc);
    }

    void Entity::AddComponent(Component* component)
    {
        m_Components.push_back(component);
    }

    void Entity::OnSerialize(ucc::ISerializer& serializer)
    {
        Object::OnSerialize(serializer);
        serializer.SerializeArray("Components", m_Components);
    }
}
