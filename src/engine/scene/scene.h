#pragma once
#include "core/coreheader.h"

namespace uniengine 
{
	class Scene
	{
	public:
        void Startup();
        void Update();
        void Shutdown();
	private:
		ucc::List<ucc::GameObject*> m_GameObjects;

	};
}
