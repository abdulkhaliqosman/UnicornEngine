#pragma once

#include "engine/core/coreheader.h"

namespace unigamecore
{
    class Component;
    class TransformComponent;

    class Entity : public ucc::Object
    {
    public:
        inline Entity(ucc::InstanceID id, const ucc::String& name) : ucc::Object(id, name) {}
        inline ~Entity() override {}

        inline const char* GetClassStr() const override { return "Entity"; }

        void Startup();
        void Update();
        void AddTransform(TransformComponent* tc);
        void AddComponent(Component* component);
        
        void OnSerialize(ucc::ISerializer& serializer) override;

        bool HasTransform() const { return m_Transform == nullptr; }
        TransformComponent* GetTransform() { return m_Transform; }
    private:

        ucc::List<Component*> m_Components;
        TransformComponent* m_Transform = nullptr;
    };
}
