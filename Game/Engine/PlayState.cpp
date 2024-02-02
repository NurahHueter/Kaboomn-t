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
        scoreClock.restart();
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
        std::cout << scoreClock.getElapsedTime().asSeconds() << std::endl;
        GameObjectManager::instance().update(deltaTime);
        PhysicsManager::instance().update();
        auto plantObjects = GameObjectManager::instance().getObjectsByType(Plants);
        auto cowObjects = GameObjectManager::instance().getObjectsByType(Cow);
        auto& playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();





        if (InputManager::instance().isKeyUp("space", 1))
        {
            

            for (auto p : plantObjects)
            {
                auto plant = p.lock();
                if (plant)
                {
                    float distance = std::sqrt(std::pow(plant->getPosition().x - playerPosition.x, 2) + std::pow(plant->getPosition().y - playerPosition.y, 2));
                    if (distance < 32.f)
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


        if (InputManager::instance().isKeyUp("pet", 1))
        {
            for (auto p : plantObjects)
            {
                auto plant = p.lock();
                if (plant)
                {
                    float distance = std::sqrt(std::pow(plant->getPosition().x - playerPosition.x, 2) + std::pow(plant->getPosition().y - playerPosition.y, 2));
                    if (distance < 32.f)
                    {
                        // Pflanze gie�en
                        auto plantComponent = plant->getComponent<PlantCmp>();
                        if (plantComponent)
                        {
                            AssetManager::instance().m_Music["Pet"]->play();
                            plantComponent->pet();
                        }
                    }
                }
            }
        }


        if (InputManager::instance().isMouseDown("leftclick", 1))
        {
            for (auto c : cowObjects)
            {
                auto cow = c.lock();
                if (cow)
                {
                    float distance = std::sqrt(std::pow(cow->getPosition().x - playerPosition.x, 2) + std::pow(cow->getPosition().y - playerPosition.y, 2));
                    if (distance < 32.f)
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


        const auto coll_pairs = PhysicsManager::instance().getCollisionPairs();
        for (const auto p : coll_pairs)
        {
        

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
              
                AssetManager::instance().m_Music["Water"]->play();
                p.second->getComponent<WaterNotiCmp>()->addWater();
               
            }
            if (p.first->getType() == Cow && p.second->getType() == ObjectType::Plants)
            {
                p.second->getComponent<PlantCmp>()->cowAttack(true);
            }
        }

        if (plantObjects.size() < 12)
        {
            std::cout << "Verloren" << std::endl;
            AssetManager::instance().m_Music["BackGround"]->stop();
            GameStateManager::instance().setState("EndState");
            PlayState::exit();
        }
    }

    void PlayState::draw()
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();

       /*
           for (auto body : PhysicsManager::instance().m_bodies)
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
    //     // Score Clock anzeigen
    //sf::Text scoreText;
    //scoreText.setFont(*AssetManager::instance().m_Font["font"]);
    //scoreText.setCharacterSize(8);
    //scoreText.setFillColor(sf::Color::Black);

    //int score = scoreClock.getElapsedTime().asSeconds();
    //std::string scoreString = "Score: " + std::to_string(score);

    //scoreText.setString(scoreString);

    ////auto player = 
    ////// Position rechts oben
    ////float x = RenderManager::instance().getWindow().getSize().x/2 ;
    ////float y = RenderManager::instance().getWindow().getSize().y / 2;

    ////scoreText.setPosition(GameObjectManager::instance().getGameObject("Player")->getPosition()- sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2, RenderManager::instance().getWindow().getSize().y / 2));
    //scoreText.setPosition(GameObjectManager::instance().getGameObject("Player")->getPosition() - sf::Vector2f(200.f, 100.f));
    //RenderManager::instance().getWindow().draw(scoreText);
        RenderManager::instance().getWindow().display();
    }
}