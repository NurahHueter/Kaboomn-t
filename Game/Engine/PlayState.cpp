/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
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
    sf::Clock PlayState::scoreClock;
    void PlayState::init()
    {
        AssetManager::instance().LoadMusic("BackGround", "../Engine/Assets/Sounds/8-bit-dream-land-142093.mp3");
		AssetManager::instance().LoadSoundBuffer("Explosion", "../Engine/Assets/Sounds/hq-explosion-6288.mp3");
		AssetManager::instance().LoadSoundBuffer("axe", "../Engine/Assets/Sounds/axe-slash-1-106748.mp3");
		AssetManager::instance().LoadSoundBuffer("pet", "../Engine/Assets/Sounds/seHm.mp3");
		AssetManager::instance().LoadSoundBuffer("water", "../Engine/Assets/Sounds/splash-6213.mp3");
		AssetManager::instance().LoadSoundBuffer("cow", "../Engine/Assets/Sounds/animalhowling-107316.mp3");


        scoreClock.restart();
       //map
        tson::Tileson t;
        const fs::path tileMapresourcePath = { "../Engine/Assets/Tiled" };
        const std::unique_ptr<tson::Map> map = t.parse(tileMapresourcePath / "game.tmj");

        
        mapTile.loadMap(map, tileMapresourcePath);
       
        const auto& mapGo = std::make_shared<GameObject>("map");
        mapTile.getTiledLayer(*mapGo, map);
        mapTile.getObjectLayer(map);
        mapGo->init();

        GameObjectManager::instance().addGameObject(mapGo);

        //sound

        AssetManager::instance().m_Music["BackGround"]->setVolume(40);
        AssetManager::instance().m_Music["BackGround"]->play();
        AssetManager::instance().m_Music["BackGround"]->setLoop(true);

        m_waterSound.setBuffer(*AssetManager::instance().m_SoundBuffer["water"]);
        m_petSound.setBuffer(*AssetManager::instance().m_SoundBuffer["pet"]);
        m_axeSound.setBuffer(*AssetManager::instance().m_SoundBuffer["axe"]);
        m_petSound.setVolume(60);
        
    }

    void PlayState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
        AssetManager::instance().shutdown();
    }

    void PlayState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
        PhysicsManager::instance().update();
        auto plantObjects = GameObjectManager::instance().getObjectsByType(Plants);
        auto cowObjects = GameObjectManager::instance().getObjectsByType(Cow);
        auto player = GameObjectManager::instance().getGameObject("Player");


        if (plantObjects.size() < 12 && plantObjects.size()!=0)
        {
            GameStateManager::instance().setState("EndState");
        }


        if (InputManager::instance().isKeyPressed("space",1))
        {
            if (!m_spaceKeyPressedPreviously && player->getComponent<WaterNotiCmp>()->m_waterAmount > 0)
            {
                player->getComponent<WaterNotiCmp>()->looseWater();
                m_waterSound.play();

                for (auto p : plantObjects)
                {
                    auto plant = p.lock();
                    if (plant)
                    {
                        float distance = std::pow(plant->getPosition().x - player->getPosition().x, 2) + std::pow(plant->getPosition().y - player->getPosition().y, 2);
                        if (distance < m_radiusSquared)
                        {
                            auto plantComponent = plant->getComponent<PlantCmp>();
                            if (plantComponent)
                            {
                                plantComponent->watering();
                            }
                        }
                    }
                }
            }
         
           m_spaceKeyPressedPreviously = true;
        }
        else
        {
            m_spaceKeyPressedPreviously = false;
        }



       if (InputManager::instance().isKeyPressed("pet", 1))
        {
            for (auto p : plantObjects)
            {
                auto plant = p.lock();
                if (plant)
                {
                    float distance = std::pow(plant->getPosition().x - player->getPosition().x, 2) + std::pow(plant->getPosition().y - player->getPosition().y, 2);
                    if (distance < m_radiusSquared)
                    {
                        auto plantComponent = plant->getComponent<PlantCmp>();
                        if (plantComponent)
                        {
                        
                            m_petSound.play();
                            plantComponent->pet();
                        }
                    }
                }
            }
        }
       else if (InputManager::instance().isMousePressed("leftclick", 1) && !m_leftclickPressedPreviouslyTool)
       {
           m_leftclickPressedPreviouslyTool = true;
           m_axeSound.play();
           for (auto c : cowObjects)
           {
               auto cow = c.lock();
               if (cow)
               {
                   float distance = std::pow(cow->getPosition().x - player->getPosition().x, 2) + std::pow(cow->getPosition().y - player->getPosition().y, 2);
                   if (distance < m_radiusSquared)
                   {
                       auto plantComponent = cow->getComponent<CowAICmp>();
                       if (plantComponent)
                       {
                           plantComponent->m_despawn = true;
                       }
                   }
               }
           }
       }
       else if (!InputManager::instance().isMousePressed("leftclick", 1))
       {
           m_leftclickPressedPreviouslyTool = false;
       }

        for (auto c : cowObjects)
        {
            auto cow = c.lock();
            if (cow)
            {
                auto cowAICmp = cow->getComponent<CowAICmp>();
                if (cowAICmp && cowAICmp->m_isEating)
                {
                    for (auto p : plantObjects)
                    {
                        auto plant = p.lock();

                        if (plant)
                        {
                            float distance = std::pow(plant->getPosition().x - cow->getPosition().x, 2) + std::pow(plant->getPosition().y - cow->getPosition().y, 2);
                            if (distance < m_radiusSquared*4)
                            {
                                auto plantComponent = plant->getComponent<PlantCmp>();
                                if (plantComponent)
                                {
                                    m_petSound.play();
                                    plantComponent->cowAttack(true);
                                }
                                else
                                {
                                    plantComponent->cowAttack(false);
                                }
                            }
                        }
                    }
                }
            }
        }


        


        const auto coll_pairs = PhysicsManager::instance().getCollisionPairs();
        for (const auto p : coll_pairs)
        {
        

           /* if ((p.first->getType() == ObjectType::Plants 
                && p.first->getComponent<PlantAICmp>()->isExploding()) 
                && p.second->getType() == Plants)
            {
                    p.second->getComponent<PlantCmp>()->getHitfromExplosion();
            }*/
            if (p.first->getType() == ObjectType::Trigger 
                && p.second->getType() == Player
                && InputManager::instance().isKeyPressed("space",1))
            {
                m_waterSound.play();
                p.second->getComponent<WaterNotiCmp>()->addWater();
               
            }           
        }

       
    }

    void PlayState::draw()
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().display();
    }
}