#pragma once

#include "core/coreheader.h"
#include "render/manager/rendermanager.h"
#include "editor/server/editornetworkserver.h"

namespace uniengine
{
	class Scene;

	class Engine
	{
	public:
		Engine();
		void Init();
        void Startup();
        void Update();
        void Shutdown();

		inline unirender::RenderManager& GetRenderManager() { return m_RenderManager; }

	private:
		unirender::RenderManager m_RenderManager;

		EditorNetworkServer m_EditorServer;
		ucc::MemoryManager m_MemoryManager;
		ucc::ThreadManager m_ThreadManager;
		ucc::InputManager m_InputManager;
		ucc::NetworkThread m_NetworkThread;

		Scene* m_Scene;
	};
}
