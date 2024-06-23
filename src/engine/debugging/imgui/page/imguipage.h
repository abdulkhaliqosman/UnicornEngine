#pragma once

namespace unidebug
{
    class ImguiPage
    {
    public:
        virtual void Update() = 0;
        virtual const char* GetMenu() = 0;
        virtual const char* GetMenuItem() = 0;
        bool& GetShowPage() { return m_ShowPage; }
    private:
        bool m_ShowPage = false;
    };
}