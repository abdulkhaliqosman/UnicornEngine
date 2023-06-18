// UnicornEngine.cpp : Defines the entry point for the application.

#include <Windows.h>
#include "engine/engineheader.h"

#if defined(UNICORN_EDITOR)
#include "editor/editor/editor.h"
#endif

#if defined(UNICORN_CLIENT)
#include "client/clientheader.h"
#endif

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    uce::Engine engine;

#if defined(UNICORN_EDITOR)
    unieditor::Editor editor;
    editor.SetEngine(&engine);

    editor.Run();
#endif

#if defined(UNICORN_CLIENT)
    ucl::WindowsParams winParams{ hInstance, hPrevInstance, lpCmdLine, nCmdShow };
    ucl::WindowsClient client(winParams);

    client.SetEngine(&engine);
    
    client.Run();
#endif



	return 0;
}

#if defined(NDEBUG)
#pragma comment(linker, "/subsystem:windows")
#else
#pragma comment(linker, "/subsystem:console")
int main(int, const char**)
{
    return WinMain(GetModuleHandle(nullptr), nullptr, GetCommandLine(),
        SW_SHOWDEFAULT);
}
#endif
