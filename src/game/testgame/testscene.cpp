#include "testscene.h"
#include <tuple>
#include "engine/gamecore/components/transformcomponent.h"
#include "engine/gamecore/components/rendercomponent.h"

namespace testgame
{
    static ucr::RenderObject* CreateCharacterRenderObject()
    {
        auto* asset = uniassets::GLTFFileAsset::ImportFromFile("../content/meshes/mixamogirl.glb");
        ucr::RenderManager* rm = ucr::RenderManager::GetInstance();
        if (rm != nullptr)
        {
            auto* mesh = rm->CreateMeshObject(*asset->GetMeshes()[0]);
            auto* material = rm->CreateMaterialObject(*asset->GetMaterials()[0]);
            auto* obj = rm->CreateRenderObject();

            obj->SetMesh(mesh);
            obj->SetMaterial(material);

            return obj;
        }
        
        return nullptr;
    }

    static ucg::TransformComponent* CreateTransformComponent(ucg::Entity* entity, float x, float y, float z)
    {
        static int s_ObjectId = 100; // TODO: consolidate all object creation in an ObjectManager
        auto* transform = ucNew(ucg::TransformComponent, ++s_ObjectId, "TransformComponent", entity);
        transform->SetPosition(ucc::Vector4f(x, y, z));
        return transform;
    }

    static ucg::RenderComponent* CreateRenderComponent(ucg::Entity* entity, ucr::RenderInstance* instance)
    {
        static int s_ObjectId = 200; // TODO: consolidate all object creation in an ObjectManager
        auto* render = ucNew(ucg::RenderComponent, ++s_ObjectId, "RenderComponent", entity);
        render->SetRenderInstance(instance);
        return render;
    }

    void CreateCamera()
    {
        ucr::RenderManager* rm = ucr::RenderManager::GetInstance();
        if (rm != nullptr)
        {
            auto* cam = rm->CreateCamera();

            constexpr float TAN45 = 1.0f;
            constexpr float DEFAULT_NEARPLANE = 0.001f;
            constexpr float DEFAULT_FARPLANE = 1000.0f;
            constexpr float ASPECT_RATIO_16_9 = 16.0f / 9.0f;
            constexpr float ASPECT_RATIO_4_3 = 4.0f / 3.0f;

            float top = TAN45 * DEFAULT_NEARPLANE / ASPECT_RATIO_4_3;
            float right = TAN45 * DEFAULT_NEARPLANE;

            // cam->SetPerspective(DEFAULT_NEARPLANE, DEFAULT_FARPLANE, top, right);
            // cam->SetPerspectiveFov(TAN45, ASPECT_RATIO_4_3, DEFAULT_NEARPLANE, DEFAULT_FARPLANE);
            rm->SetActiveCamera(cam);
        }
    }

    void TestScene::Startup()
    {
        auto* character = CreateCharacterRenderObject();

        constexpr int INST_CNT = 1;
        

        for (int i = -INST_CNT; i <= INST_CNT; ++i)
        {
            for (int j = -INST_CNT; j <= INST_CNT; ++j)
            {
                for (int k = -INST_CNT; k <= INST_CNT; ++k)
                {
                    auto* entity = CreateEntity("MixamoGirl");

                    auto* inst = character->CreateInstance();
                    auto sMtx = ucc::Transform::Scale(ucc::Vector4f::One()); // ucc::Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
                    auto tMtx = ucc::Transform::Translation(i * 3.0f, j * 3.0f, k * 3.0f);
                    auto* transform = CreateTransformComponent(entity, i * 3.0f, j * 3.0f, k * 3.0f);
                    entity->AddTransform(transform);
                    inst->SetModelTransform(sMtx * tMtx);

                    auto* render = CreateRenderComponent(entity, inst);
                    entity->AddComponent(render);
                }
            }
        }
        CreateCamera();

        Scene::Startup();
    }

    void TestScene::Update()
    {
        Scene::Update();
    }

    void TestScene::Shutdown()
    {
        Scene::Shutdown();
    }
}
