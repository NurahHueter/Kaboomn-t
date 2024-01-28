#include "pch.h"
#include "GameObjectManager.h"

#include "Debug.h"
namespace mmt_gd
{

    void GameObjectManager::init()
    {
    }

    void GameObjectManager::shutdown()
    {
        m_gameObjects.clear();
    }

    void GameObjectManager::update(const float deltaTime)
    {
        std::vector<GameObject::Ptr> gameObjectsToDelete{};

        for (const auto& goPair : getGameObjects())
        {
            if (goPair.second->isMarkedForDelete())
            {
                gameObjectsToDelete.push_back(goPair.second);
            }
            else if (goPair.second->isActive())
            {
                goPair.second->update(deltaTime);
            }
        }
        for (const auto& go : gameObjectsToDelete)
        {
            removeGameObject(go);
        }
    }

        void GameObjectManager::addGameObject(const GameObject::Ptr & gameObject)
        {
            ffAssertMsg(m_gameObjects.find(gameObject->getId()) == m_gameObjects.end(),
                "Game object with this m_id already exists " + gameObject->getId())

                m_gameObjects[gameObject->getId()] = gameObject;

        }

        GameObject::Ptr GameObjectManager::getGameObject(const std::string& id) const
        {
            auto it = m_gameObjects.find(id);
            if (it != m_gameObjects.end())
            {
                return it->second;
            }
            else
            {
                ffErrorMsg("Could not find gameobject with id " + id);
                return nullptr;
            }
        }


        void GameObjectManager::removeGameObject(const std::shared_ptr<GameObject>&go)
        {
            if (m_gameObjects.find(go->getId()) != m_gameObjects.end())
            {
                m_gameObjects.erase(go->getId());
            }
        }

        std::vector<std::weak_ptr<GameObject>> GameObjectManager::getObjectsByType(ObjectType type)
        {
            std::vector <std::weak_ptr<GameObject>> gameObjectPointers;

            for (const auto& goPair : getGameObjects())
            {
                if (type == goPair.second->getType())
                {
                    gameObjectPointers.push_back(goPair.second);
                }
            }
            return gameObjectPointers;
        }
        std::vector<std::weak_ptr<GameObject>> GameObjectManager::getObjectsByArea(sf::Rect<float>& area)
        {
            std::vector <std::weak_ptr<GameObject>> gameObjectPointers;

            for (const auto& goPair : getGameObjects())
            {
                if (area.contains(goPair.second->getPosition()))
                {
                    gameObjectPointers.push_back(goPair.second);
                }
            }
            return gameObjectPointers;
        };
}