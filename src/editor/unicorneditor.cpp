// UnicornEngine.cpp : Defines the entry point for the application.

#include "engine/engineheader.h"

#if defined(UNICORN_EDITOR)
#include "editor/editor/editor.h"
#endif
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    
    
    // uce::Engine engine;
    // 
    unieditor::Editor editor;
    // editor.SetEngine(&engine);
    // 


    if (false == CreateProcess("unicornclient.exe", nullptr,
        nullptr, nullptr, false,
        0, nullptr, nullptr, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    editor.Init();
    editor.Run();

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

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
