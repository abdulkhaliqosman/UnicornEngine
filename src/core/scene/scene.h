#pragma once
#include "core/coreheader.h"

namespace unicore
{
	class Scene
	{
	public:
        void Startup();
        void Update();
        void Shutdown();

		void SaveScene(const TCHAR* path);
		void LoadScene(const TCHAR* path);
	private:
		ucc::List<ucc::Entity*> m_Entities;
	};
}
