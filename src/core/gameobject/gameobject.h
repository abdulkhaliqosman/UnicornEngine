#pragma once

#include "core/serializer/serializer.h"
#include "core/container/list.h"
#include "core/component/component.h"

namespace unicore
{
    class GameObject
    {
    public:
        void Serialize(ISerializer&);
        
    private:
        List<Component> m_Components;
    };
}