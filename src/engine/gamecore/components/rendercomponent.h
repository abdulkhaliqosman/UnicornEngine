#pragma once

#include "engine/render/renderheader.h"
#include "engine/gamecore/component/component.h"

namespace unigamecore
{
    class RenderComponent : public Component
    {
    public:
        RenderComponent(ucc::InstanceID id, const ucc::String& name, Entity* owner) : Component(id, name, owner) {}
		inline ~RenderComponent() override {}

		void OnSerialize(ucc::ISerializer& serializer) override;
		inline const char* GetClassStr() const override { return "RenderComponent"; }

		void Update() override;

        inline void SetRenderInstance(ucr::RenderInstance* value) { m_RenderInstance = value; }
        inline const ucr::RenderInstance* GetRenderInstance() const { return m_RenderInstance; }
        inline ucr::RenderInstance* GetRenderInstance() { return m_RenderInstance; }

    private:
        ucr::RenderInstance* m_RenderInstance;
    };
}
