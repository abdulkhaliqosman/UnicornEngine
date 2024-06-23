#include "scene.h"
#include "entity/entity.h"

namespace unigamecore
{
    void Scene::Initialize()
    {
        m_State = SceneState::Startup;
    }

    void Scene::Startup()
    {
        m_State = SceneState::Update;
    }

    void Scene::Update()
    {
        for (Entity* entity : m_Entities)
        {
            entity->Update(); // TODO move update into separate systems
        }
    }

    void Scene::Shutdown()
    {
        m_State = SceneState::Inactive;
    }

    void Scene::OnSerialize(ucc::ISerializer& serializer)
    {
        Object::OnSerialize(serializer);
        serializer.SerializeArray("Entities", m_Entities);
        
    }

    Entity* Scene::CreateEntity(const ucc::String& name)
    {
        static int s_ObjectId = 0; // TODO: consolidate all object creation in an ObjectManager

        Entity* entity = ucNew(Entity, ++s_ObjectId, name);

        m_Entities.push_back(entity);

        return entity;
    }
}
