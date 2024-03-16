#pragma once

#include "core/coreheader.h"
#include "render/manager/rendermanager.h"
#include "editor/server/editornetworkserver.h"

namespace uniplatform
{
	class  WindowsPlatforma;
}

namespace uniengine
{
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
		
		inline ucr::RenderManager& GetRenderManager() { return m_RenderManager; }
		inline uniplatform::WindowsPlatform* GetWindowsPlatform() { return m_WindowsPlatform; }
		inline void SetWindowsPlatform(uniplatform::WindowsPlatform* platform) { m_WindowsPlatform = platform; }

	private:
		ucr::RenderManager m_RenderManager;
		uniplatform::WindowsPlatform* m_WindowsPlatform = nullptr;

		EditorNetworkServer m_EditorServer;
		ucc::MemoryManager m_MemoryManager;
		ucc::ThreadManager m_ThreadManager;
		ucc::InputManager m_InputManager;
		ucc::NetworkThread m_NetworkThread;

		ucc::Scene* m_Scene = nullptr;

		void FakeSceneStartup();
		void FakeSceneUpdate();
	};
}
