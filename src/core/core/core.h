#pragma once

#include "core/memory/manager/memorymanager.h"
#include "core/thread/manager/threadmanager.h"
#include "core/windows/windowmanager/windowmanager.h"
#include "core/input/inputmanager.h"

namespace unicore
{
    struct CoreParams
    {
        WindowsParams windowsParams;
    };

	class Core
	{
	public:
		Core(const CoreParams& coreParams);
        void Startup();
		void Update();
        void Shutdown();

		MemoryManager& GetMemoryManager() { return m_MemoryManager; }
		ThreadManager& GetThreadManager() { return m_ThreadManager; }
		WindowManager& GetWindowManager() { return m_WindowManager; }
		InputManager& GetInputManager() { return m_InputManager; }

	private:
		MemoryManager m_MemoryManager;
		ThreadManager m_ThreadManager;
		WindowManager m_WindowManager;
		InputManager m_InputManager;
	};
}
