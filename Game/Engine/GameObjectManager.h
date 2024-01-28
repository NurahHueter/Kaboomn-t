#pragma once
#include <string>
#include "GameObject.h"
#include "ObjectTypes.h"
namespace mmt_gd
{
    struct GameObjectManager
    {
        using GameObjectMap = std::map<std::string, GameObject::Ptr>;

        static
            GameObjectManager&
            instance()
        {
            static GameObjectManager s;
            return s;
        } 

        GameObjectManager(const GameObjectManager&) = delete;
        GameObjectManager& operator = (const GameObjectManager&) = delete;

        static void     init();
        void            shutdown();
        void            update(float deltaTime);
        void            addGameObject(const GameObject::Ptr& gameObject);
        GameObject::Ptr getGameObject(const std::string& id) const;

        GameObjectMap& getGameObjects()
        {
            return m_gameObjects;
        }

        void removeGameObject(const std::shared_ptr<GameObject>& go);

        std::vector<std::weak_ptr<GameObject>> getObjectsByType(ObjectType type);
        std::vector<std::weak_ptr<GameObject>> getObjectsByArea(sf::Rect<float>& area);

    private:
        GameObjectManager() {}
        ~GameObjectManager() {}

        GameObjectMap m_gameObjects;
        
    };
}