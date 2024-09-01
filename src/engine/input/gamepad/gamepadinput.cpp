#include "gamepadinput.h"
#include <Windows.h>

#pragma comment(lib, "XInput.lib")

namespace Unicorn
{
	void GamepadInput::Update()
	{
		DWORD dwResult;
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(m_Index, &state);
		

		if (dwResult == ERROR_SUCCESS)
		{
			if (m_IsConnected == false)
			{
				m_IsConnected = true;
				// TODO trigger on connect event
			}
			m_CurrentBuffer = NextBuffer();
			m_State[m_CurrentBuffer] = state;

		}
		else if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
		{
			if (m_IsConnected == true)
			{
				m_IsConnected = false;
				// TODO trigger on disconnect event
			}
		}
		else
		{
			// TODO handle error
		}
	}

	GamepadInputList::GamepadInputList()
		:m_Inputs{0,1,2,3}
	{
		
	}

	void GamepadInputList::Update()
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			// ERROR_DEVICE_NOT_CONNECTED
			m_Inputs[i].Update();
		}
	}
}
