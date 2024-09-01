#include "imguiserializer.h"
#include "imgui.h"


namespace unidebug
{
    void ImguiSerializer::Serialize(const char* name)
    {
        ImGui::Text(name);
    }

    void ImguiSerializer::Serialize(const char* name, int8_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, int16_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, int32_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, int64_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, uint8_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, uint16_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, uint32_t&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, uint64_t& val)
    {
        ImGui::InputScalar(name, ImGuiDataType_U64, &val);
    }

    void ImguiSerializer::Serialize(const char* name, float&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, double&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, ucc::Vector4f& val)
    {
        ImGui::InputScalarN(name, ImGuiDataType_Float, &val.GetData(), 4);
    }

    void ImguiSerializer::Serialize(const char* name, ucc::Quaternion4f& val)
    {
        ImGui::InputScalarN(name, ImGuiDataType_Float, &val.GetData(), 4);
    }

    void ImguiSerializer::Serialize(const char* name, ucc::Matrix4x4f&)
    {

    }

    void ImguiSerializer::Serialize(const char* name, ucc::String& string)
    {
        static constexpr size_t BufferSize = 1024;
        char buf[BufferSize] = "\0";
        strcpy_s(buf, string.c_str());

        ImGui::InputText(name, buf, BufferSize);

        string = buf;
    }

    void ImguiSerializer::SerializeObject(ucc::Object* object)
    {
        // assert nullptr
        if (ImGui::TreeNode((void*)object, "%s (%llu)", object->GetName().c_str(), object->GetInstanceID()))
        {
            ImGui::PushID(object->GetInstanceID());

            (object)->OnSerialize(*this);

            ImGui::PopID();
            ImGui::TreePop();
        }

        
    }

    bool ImguiSerializer::SerializeArrayBegin(const char* name, uint64_t& size)
    {
        if (ImGui::TreeNode(name))
        {
            Serialize("Size", size);
            return true;
        }
        return false;
    }

    void ImguiSerializer::SerializeArrayEnd(const char* name)
    {
        ImGui::TreePop();
    }
}
