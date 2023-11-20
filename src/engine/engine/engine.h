#pragma once

#include "core/coreheader.h"
#include "render/manager/rendermanager.h"
#include "editor/server/editornetworkserver.h"

namespace uniplatform
{
	class  WindowsPlatform;
}

namespace uniengine
{
	class Scene;

	class Engine
	{
	public:
		Engine();

		void Run();

		void Initialize();
		void Uninitialize();
        void Startup();
        void Update();
        void Shutdown();
		
		inline unirender::RenderManager& GetRenderManager() { return m_RenderManager; }
		inline uniplatform::WindowsPlatform* GetWindowsPlatform() { return m_WindowsPlatform; }
		inline void SetWindowsPlatform(uniplatform::WindowsPlatform* platform) { m_WindowsPlatform = platform; }

	private:
		unirender::RenderManager m_RenderManager;
		uniplatform::WindowsPlatform* m_WindowsPlatform = nullptr;

		EditorNetworkServer m_EditorServer;
		ucc::MemoryManager m_MemoryManager;
		ucc::ThreadManager m_ThreadManager;
		ucc::InputManager m_InputManager;
		ucc::NetworkThread m_NetworkThread;

		Scene* m_Scene;

		void FakeSceneUpdate();
	};
}
