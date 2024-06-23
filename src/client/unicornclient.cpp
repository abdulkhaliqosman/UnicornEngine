// unicornclient.cpp : Defines the entry point for the application.

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "engine/platform/windows/windowsplatform.h"
#include "engine/engineheader.h"
#include "game/testgame/testscene.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    uniplatform::WindowsPlatform winPlatform(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    uce::Engine engine;
    testgame::TestScene scene(-1, "TestScene");

    engine.SetWindowsPlatform(&winPlatform);
    engine.GetSceneManager().LoadScene(&scene);
    engine.Run();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

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
