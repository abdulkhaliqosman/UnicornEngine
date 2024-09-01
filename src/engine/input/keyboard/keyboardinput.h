#pragma once

#include "platform/windows/windowsplatform.h"

namespace Unicorn
{
	struct KeyArray
	{
		uint32_t keys[8] = { 0 };

		inline bool GetKey(uint32_t index) const { return keys[index / 32] & (1 << (index % 32)); }
		inline void SetKey(uint32_t index) { keys[index / 32] |= (1 << (index % 32)); }
		inline void UnsetKey(uint32_t index) { keys[index / 32] &= ~(1 << (index % 32)); }
	};

	class KeyboardInput
	{
	public:
		bool GetKey(uint32_t index) const;
		bool GetKeyDown(uint32_t index) const;
		bool GetKeyUp(uint32_t index) const;

		void SetKey(uint32_t index);
		void UnsetKey(uint32_t index);

		void SwapBuffer();
	private:
		KeyArray m_KeyArray[2];
		uint32_t m_CurrentBuffer = 0;
	};
}
