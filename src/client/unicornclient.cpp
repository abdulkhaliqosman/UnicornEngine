// UnicornEngine.cpp : Defines the entry point for the application.

#include "client/clientheader.h"

#include <Windows.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    uce::Engine engine;
    ucl::WindowsParams winParams{ hInstance, hPrevInstance, lpCmdLine, nCmdShow };
    ucl::WindowsClient client(winParams);

    client.SetEngine(&engine);

    client.Run();

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
