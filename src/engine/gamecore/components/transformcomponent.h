#pragma once

#include "engine/gamecore/component/component.h"

namespace unigamecore
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(ucc::InstanceID id, const ucc::String& name, Entity* owner) : Component(id, name, owner) {}
        inline ~TransformComponent() override {}

        void OnSerialize(ucc::ISerializer& serializer) override;
        inline const char* GetClassStr() const override { return "TransformComponent"; }

        void Update() override;

        ucc::Matrix4x4f ToLocalMatrix() const;
        ucc::Matrix4x4f ToGlobalMatrix() const { return m_Transform.ToMatrix(); } // TODO: hook up global matrix

        inline TransformComponent* GetParent() { return m_Parent; }
        inline const TransformComponent* GetParent() const { return m_Parent; }
        inline void SetParent(TransformComponent* transform) { m_Parent = transform; }

        const ucc::Vector4f& GetPosition() const { return m_Transform.GetPosition(); }
        ucc::Vector4f& GetPosition() { return m_Transform.GetPosition(); }
        void SetPosition(const ucc::Vector4f& pos) { m_Transform.SetPosition(pos); }

        const ucc::Vector4f& GetScale() const { return m_Transform.GetScale(); }
        ucc::Vector4f& GetScale() { return m_Transform.GetScale(); }
        void SetScale(const ucc::Vector4f& scale) { m_Transform.SetScale(scale); }

        const ucc::Quaternion4f& GetRotation() const { return m_Transform.GetRotation(); }
        ucc::Quaternion4f& GetRotation() { return m_Transform.GetRotation(); }
        void SetRotation(const ucc::Quaternion4f& rot) { m_Transform.SetRotation(rot); }

    private:
        ucc::Transform m_Transform;

        TransformComponent* m_Parent = nullptr;
    };
}