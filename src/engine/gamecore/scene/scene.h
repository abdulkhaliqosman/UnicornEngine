#pragma once

#include "core/coreheader.h"

namespace unigamecore
{
	class Entity;

	enum class SceneState
	{
		Uninitialized,
		Startup,
		Update,
		Shutdown,
		Inactive
	};

	class Scene : public ucc::Object
	{
	public:
		inline Scene(ucc::InstanceID id, const ucc::String& name) : Object(id, name) {}
		inline ~Scene() override {}

        virtual void Initialize();
        virtual void Startup();
        virtual void Update();
        virtual void Shutdown();

		void OnSerialize(ucc::ISerializer& serializer) override;

		Entity* CreateEntity(const ucc::String& name);
		inline SceneState GetState() const { return m_State; }

	private:
		ucc::List<Entity*> m_Entities;
		SceneState m_State = SceneState::Uninitialized;
	};
}
