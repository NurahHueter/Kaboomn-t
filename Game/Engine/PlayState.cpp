#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "SpriteAnimationCmp.h"
#include "PlantCmp.h"
#include "PlantAICmp.h"
#include "GameState.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "CowAICmp.h"
#include "ToolCmp.h"
#include "WaterNotiCmp.h"
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

        //music
        AssetManager::instance().LoadMusic("Hm", "../Engine/Assets/Sounds/seHm.mp3");
        
        AssetManager::instance().LoadMusic("BackGround", "../Engine/Assets/Sounds/8-bit-dream-land-142093.mp3");
        AssetManager::instance().m_Music["BackGround"]->play();
        AssetManager::instance().m_Music["BackGround"]->setLoop(true);
        
    }

    void PlayState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void PlayState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
        PhysicsManager::instance().update();
        

        const auto coll_pairs = PhysicsManager::instance().getCollisionPairs();
        for (const auto p : coll_pairs)
        {
            if (p.first->getType() == ObjectType::Plants && p.second->getType() == Player)
            {
                const auto& playerAnimation = GameObjectManager::instance().getGameObject("Player")->getComponent<SpriteAnimationCmp>()->getCurrentAnimation();
                if (playerAnimation == WaterDown 
                    || playerAnimation == WaterUp
                    || playerAnimation == WaterLeft
                    || playerAnimation == WaterRight)
                {
                    p.first->getComponent<PlantCmp>()->watering();
                }
                if (InputManager::instance().isKeyPressed("pet", 1))
                {
                    AssetManager::instance().m_Music["Hm"]->play();
                    p.first->getComponent<PlantCmp>()->pet();
                }
               
            }
            if (p.first->getType() == ObjectType::Cow && p.second->getType() == Player)
            {
                if (InputManager::instance().isMouseDown("leftclick", 1))
                {
                    p.first->getComponent<CowAICmp>()->m_despawn=true;
                }
            }
            if ((p.first->getType() == ObjectType::Plants 
                && p.first->getComponent<PlantAICmp>()->isExploding()) 
                && p.second->getType() == Plants)
            {
                    p.second->getComponent<PlantCmp>()->getHitfromExplosion();
            }
            if (p.first->getType() == ObjectType::Trigger 
                && p.second->getType() == Player
                && InputManager::instance().isKeyUp("space",1))
            {
                p.second->getComponent<WaterNotiCmp>()->addWater();
               
            }
            if (p.first->getType() == Cow && p.second->getType() == ObjectType::Plants)
            {
                std::cout << "WELLLLL" << std::endl;
                p.second->getComponent<PlantCmp>()->cowAttack(true);
            }
        }
    }

    void PlayState::draw()
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();

       
          /*  for (auto body : PhysicsManager::instance().m_bodies)
            {
                if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
                {
                    {
                        sf::RectangleShape m_debugGeometry;
                        m_debugGeometry.setPosition(tempP->m_shape.getPosition());
                        m_debugGeometry.setSize(tempP->m_shape.getSize());
                        m_debugGeometry.setFillColor(sf::Color::Transparent);
                        m_debugGeometry.setOutlineColor(sf::Color::Red);
                        m_debugGeometry.setOutlineThickness(2);

                        RenderManager::instance().getWindow().draw(m_debugGeometry);
                    }
                }
            }*/
        
        RenderManager::instance().getWindow().display();
    }
}