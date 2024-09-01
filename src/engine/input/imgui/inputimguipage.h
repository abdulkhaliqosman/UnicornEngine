#pragma once

#include "debugging/debuggingheader.h"

namespace Unicorn
{
	class InputImguiPage : public ucd::ImguiPage
	{
	public:
		void Update() override;
		inline const char* GetMenu() override { return "Input"; }
		inline const char* GetMenuItem() override { return "Input"; }
	};
}