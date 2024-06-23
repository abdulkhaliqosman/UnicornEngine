#include "imguimanager.h"
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "imgui/page/imguipage.h"

namespace unidebug
{
    void ImguiManager::Initialize()
    {
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplWin32_Init(m_HWnd);
        ImGui_ImplDX11_Init(m_Device, m_DeviceContext);

        ms_Instance = this;
    }

    void ImguiManager::EarlyUpdate()
    {
        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::Text("Hello, world!");

        static bool s_ShowDemoWindow = true;
        ImGui::ShowDemoWindow(&s_ShowDemoWindow);

        
    }

    void ImguiManager::LateUpdate()
    {
        ShowPages();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    void ImguiManager::Shutdown()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiManager::AddPage(ImguiPage* page)
    {
        m_Pages[page->GetMenu()].push_back(page);
    }

    void ImguiManager::ShowPages()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_MenuBar;
        for (auto& menu : m_Pages)
        {
            for (auto& page : menu.second)
            {
                if (page->GetShowPage())
                {
                    page->Update();
                }
            }
        }

        if (ImGui::Begin("Unicorn Engine", NULL, window_flags))
        {
            if (ImGui::BeginMenuBar())
            {
                //TODO: Page Tree instead of everything on the main menu bar
                for (auto& menu : m_Pages)
                {
                    if (ImGui::BeginMenu(menu.first))
                    {
                        for (auto& page : menu.second)
                        {
                            ImGui::MenuItem(page->GetMenuItem(), nullptr, &page->GetShowPage());
                        }
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenuBar();
            }
        }
        ImGui::End();
    }
}