#include "keyboardinput.h"

namespace Unicorn
{
	bool KeyboardInput::GetKey(uint32_t index) const
	{
		uint32_t a = m_CurrentBuffer;
		return m_KeyArray[a].GetKey(index);
	}

	bool KeyboardInput::GetKeyDown(uint32_t index) const
	{
		uint32_t a = m_CurrentBuffer;
		uint32_t b = (m_CurrentBuffer + 1) % 2;

		return m_KeyArray[a].GetKey(index) && !m_KeyArray[b].GetKey(index);
	}

	bool KeyboardInput::GetKeyUp(uint32_t index) const
	{
		uint32_t a = m_CurrentBuffer;
		uint32_t b = (m_CurrentBuffer + 1) % 2;

		return !m_KeyArray[a].GetKey(index) && m_KeyArray[b].GetKey(index);
	}

	void KeyboardInput::SwapBuffer()
	{
		// uint32_t a = m_CurrentBuffer;
		// uint32_t b = (m_CurrentBuffer + 1) % 2;

		// m_KeyArray[b] = m_KeyArray[a];
		m_CurrentBuffer = (m_CurrentBuffer + 1) % 2;
	}

	void KeyboardInput::SetKey(uint32_t index)
	{
		m_KeyArray[m_CurrentBuffer].SetKey(index);
	}

	void KeyboardInput::UnsetKey(uint32_t index)
	{
		m_KeyArray[m_CurrentBuffer].UnsetKey(index);
	}
}
