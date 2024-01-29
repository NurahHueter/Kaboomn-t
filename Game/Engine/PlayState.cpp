#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
namespace mmt_gd
{
    void PlayState::init()
    {
        //map
        tson::Tileson t;
        const fs::path tileMapresourcePath = { "Assets/Tiled" };
        const std::unique_ptr<tson::Map> map = t.parse(tileMapresourcePath / "game.tmj");
        mapTile.loadMap(map, tileMapresourcePath);

        const auto& mapGo = std::make_shared<GameObject>("map");
        mapTile.getTiledLayer(*mapGo, map);
        mapTile.getObjectLayer(map);
        mapGo->init();

        GameObjectManager::instance().addGameObject(mapGo);
    }

    void PlayState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void PlayState::update(float deltaTime)
    {
        PhysicsManager::instance().update();
        GameObjectManager::instance().update(deltaTime);

    

    }

    void PlayState::draw()
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();

        // for (auto body : PhysicsManager::instance().m_bodies)
        // {
        //     if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
        //     {
        //         {
        //             sf::RectangleShape m_debugGeometry;
        //             m_debugGeometry.setPosition(tempP->m_shape.getPosition());
        //             m_debugGeometry.setSize(tempP->m_shape.getSize());
        //             m_debugGeometry.setFillColor(sf::Color::Transparent);
        //             m_debugGeometry.setOutlineColor(sf::Color::Red);
        //             m_debugGeometry.setOutlineThickness(2);

        //             RenderManager::instance().getWindow().draw(m_debugGeometry);
        //         }
        //     }
        // }
        RenderManager::instance().getWindow().display();
    }
}