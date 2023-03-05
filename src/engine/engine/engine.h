#pragma once

#include "core/coreheader.h"
#include "render/manager/rendermanager.h"

namespace uniengine
{
    struct EngineParams
    {
        unicore::CoreParams coreParams;
    };

	class Engine
	{
	public:
		Engine(const EngineParams& params);
		void Run();

		inline unicore::Core& GetCore() { return m_Core; }

	private:
        void Startup();
        void Update();
        void Shutdown();
		unicore::Core m_Core;
		unirender::RenderManager m_RenderManager;
	};
}
