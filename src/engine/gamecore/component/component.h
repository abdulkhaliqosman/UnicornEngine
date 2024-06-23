#pragma once

#include "engine/core/coreheader.h"

namespace unigamecore
{
    class Entity;

    class Component : public ucc::Object
    {
    public:
        inline Component(ucc::InstanceID id, const ucc::String& name, Entity* owner) : ucc::Object(id, name), m_Owner(owner) {}
        inline ~Component() override {}

        inline void SetOwner(Entity* entity) { m_Owner = entity; }
        inline Entity* GetOwner() { return m_Owner; }
        inline const Entity* GetOwner() const { return m_Owner; }

        virtual void Update() = 0;
    private:
        Entity* m_Owner = nullptr;
    };
}
