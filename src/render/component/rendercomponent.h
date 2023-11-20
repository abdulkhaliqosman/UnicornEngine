#pragma once

#include "renderheader.h"

namespace unirender
{
    class RenderInstance;

    class RenderComponent
    {
    public:

        inline void SetRenderInstance(const RenderInstance* value) { m_RenderInstance = value; }
        inline const RenderInstance* GetRenderInstance() const { return m_RenderInstance; }
    private:
        const RenderInstance* m_RenderInstance;
    };
}
