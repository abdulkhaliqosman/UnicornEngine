#pragma once

#include "core/serializer/serializer.h"

namespace unicore
{
    using InstanceID = uint64_t;
    using ClassID = uint64_t;
    class ISerializer;

    class Object
    {
    public:
        Object(InstanceID id, const String& name) : m_InstanceID(id), m_Name(name){}
        inline virtual ~Object() {}

        inline InstanceID GetInstanceID() const { return m_InstanceID; }
        inline void SetInstanceID(InstanceID id) { m_InstanceID = id; }
        inline const String& GetName() const { return m_Name; }
        inline void SetName(const String& name) { m_Name = name; }

        virtual const char* GetClassStr() const = 0;
        virtual void OnSerialize(ISerializer& serializer) = 0;

    private:
        InstanceID m_InstanceID = 0;
        ClassID m_ClassID = 0;
        String m_Name;
    };

    inline void Object::OnSerialize(ISerializer& serializer)
    {
        serializer.Serialize("Name", m_Name);
        serializer.Serialize("InstanceID", m_InstanceID);
    }
}
