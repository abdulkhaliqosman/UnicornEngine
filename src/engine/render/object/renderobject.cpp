#include "renderobject.h"

namespace unirender
{
    void RenderObject::Shutdown()
    {
        for (auto* instance : m_Instances)
        {
            ucDelete(instance);
        }
    }

    RenderInstance* RenderObject::CreateInstance()
    {
        RenderInstance* instance = ucNew(RenderInstance);
        m_Instances.push_back(instance);
        return instance;
    }

    void RenderObject::DestroyInstance(RenderInstance* instance)
    {
        // verify
        m_Instances.erase(std::remove(m_Instances.begin(), m_Instances.end(), instance), m_Instances.end());

        ucDelete(instance);
    }
}