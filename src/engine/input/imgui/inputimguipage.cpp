#include "inputimguipage.h"
#include "imgui.h"

#include "debugging/debuggingheader.h"
#include "input/manager/inputmanager.h"

namespace Unicorn
{
	void InputImguiPage::Update()
	{
		if (ImGui::Begin("Input"))
		{
			// SceneManager* mgr = SceneManager::GetInstance();
			// Scene* scene = mgr->GetActiveScene();
			// ucd::ImguiSerializer& ser = ucd::ImguiManager::GetSerializer();
			// ser.SerializeObject(scene);

			const InputManager& mgr = InputManager::GetInstance();
			const GamepadInputList& padlist = mgr.GetGamepads();

			for (int i = 0; i < GamepadInputList::MAX_COUNT; ++i)
			{
				const GamepadInput& pad = padlist.GetGamepad(i);
				bool isConnected = pad.IsConnected();
				ImGui::Text("Gamepad [%d]: %s", i, isConnected ? "Connected" : "Disconnected");
				if (isConnected)
				{
					if (ImGui::TreeNode(&pad, "Inputs"))
					{
						ImGui::Text("A: %s", pad.GetButton(GamepadInput::Buttons::A) ? "true" : "false");
						ImGui::TreePop();
					}
				}
			}

		}
		ImGui::End();
	}
}
