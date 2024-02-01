#pragma once
#include "pch.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "ToolCmp.h"
#include "SteeringCmp.h"
#include "SpriteRenderCmp.h"
#include "CameraCmp.h"
#include "HealthCmp.h"
#include "PlantTypes.h"
#include "ObjectTypes.h"
#include "PatchCmp.h"
#include "PlantCmp.h"
#include "PlantHud.h"
#include "PlantAICmp.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
#include"AnimationTypes.h"
#include "CowAICmp.h"


namespace mmt_gd
{
    std::vector<sf::Vector2f> ObjectFactory::m_patchPositions;
    void ObjectFactory::processTsonObject(tson::Object& object, const tson::Layer& layer)
    {
        
        if (object.getType() == "Player")
        {
            loadPlayer(object, layer);
        }
        if (object.getType() == "Patch")
        {
            loadPatch(object, layer);
        }
        if (object.getType() == "Collider")
        {
            loadStaticCollider(object, layer);
        }
        if (object.getType() == "Cow")
        {
            loadCow(object, layer);
        }
    }

    void ObjectFactory::loadPlayer(tson::Object& object, const tson::Layer& layer)
    {
        auto gameObject = std::make_shared<GameObject>(object.getName());
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
        gameObject->setType(ObjectType::Player);
        std::shared_ptr<sf::Texture> texture;
        std::string texturePath;

        for (const auto* property : object.getProperties().get())
        {
            auto name = property->getName();
            if (name == "Texture")
            {
                if ((texturePath = property->getValue<std::string>()).length() > 0)
                {
                    AssetManager::instance().LoadTexture(object.getName(), texturePath);
                    texture = AssetManager::instance().m_Textures[object.getName()];
                }
            }
        }

        std::shared_ptr<SpriteAnimationCmp> animationCmp;
        if (object.getName() == "Player")
        {
            gameObject->setPlayerIdx(1);

            animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, RenderManager::instance().getWindow(),
                texture,
                8,
                24,
                false,
                8);
            animationCmp->addAnimation({
               {IdleDown, 8},
               {IdleUp, 8},
               {IdleLeft, 8},
               {IdleRight, 8},
               {MoveDown, 8},
               {MoveUp, 8},
               {MoveRight, 8},
               {MoveLeft, 8},
               {MoveDown2, 8},
               {MoveUp2, 8},
               {MoveRight2, 8},
               {MoveLeft2, 8},
               {SickleHitDown, 8},
               {SickleHitUp, 8},
               {SickleHitLeft, 8},
               {SickleHitRight, 8},
               {AxeHitDown, 8},
               {AxeHitUp, 8},
               {AxeHitLeft, 8},
               {AxeHitRight, 8},
               {WaterDown, 8},
               {WaterUp, 8},
               {WaterLeft, 8},
               {WaterRight, 8},
                });

            const auto cameraCmp = std::make_shared<CameraCmp>(*gameObject,
                RenderManager::instance().getWindow(),
                sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2.f,
                    RenderManager::instance().getWindow().getSize().y / 2.f));

            cameraCmp->setTarget(gameObject);
            gameObject->addComponent(cameraCmp);
            RenderManager::instance().addCompToLayer(layer.getName(), cameraCmp);

            gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, 100.f));
gameObject->addComponent(std::make_shared<ToolCmp>(*gameObject));
        }


        const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject,
            sf::FloatRect(gameObject->getPosition().x,
                gameObject->getPosition().y,
                object.getSize().x/2,
                object.getSize().y/2),
            false);
        gameObject->addComponent(boxCollider);


        PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
        animationCmp->init();
        RenderManager::instance().addCompToLayer(layer.getName(), animationCmp);
        gameObject->addComponent(animationCmp);

        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);

    }

  
    void ObjectFactory::loadPatch(tson::Object& object, const tson::Layer& layer)
    {
        std::shared_ptr<sf::Texture> texture;
        std::string texturePath;
        std::string type;



        auto gameObject = std::make_shared<GameObject>(object.getName());
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

        for (const auto* property : object.getProperties().get())
        {
            auto name = property->getName();
            if (name == "Texture")
            {
                if ((texturePath = property->getValue<std::string>()).length() > 0)
                {
                    AssetManager::instance().LoadTexture(object.getName(), texturePath);
                    texture = AssetManager::instance().m_Textures[object.getName()];
                }
            }
            if (name == "Type")
            {
                type = property->getValue<std::string>();
            }
        }

        auto patchCmp = std::make_shared<PatchCmp>(*gameObject, sf::FloatRect(object.getPosition().x, object.getPosition().y, object.getSize().x, object.getSize().y));
        for (int i = 0; i < 4; i++)
        {
            auto plant = loadPlants(layer, gameObject, i, type, texture);
            patchCmp->addPlant(plant);

            // Füge die Position zum Vektor hinzu
          
        }

        auto bounds = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(gameObject->getPosition(), sf::Vector2f(object.getSize().x, object.getSize().y)), true);

        gameObject->addComponent(bounds);
        gameObject->addComponent(patchCmp);
        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);
    }
    void ObjectFactory::loadCow(tson::Object& object, const tson::Layer& layer)
    {
        auto gameObject = std::make_shared<GameObject>(object.getName());
      //probieren, irgendwie zu überschreiben
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
        gameObject->setType(ObjectType::Cow);
        std::shared_ptr<sf::Texture> texture;
        std::string texturePath;
        for (const auto* property : object.getProperties().get())
        {
            auto name = property->getName();
            if (name == "Texture")
            {
                if ((texturePath = property->getValue<std::string>()).length() > 0)
                {
                    AssetManager::instance().LoadTexture(object.getName(), texturePath);
                    texture = AssetManager::instance().m_Textures[object.getName()];
                }
            }
        }

        std::shared_ptr<SpriteAnimationCmp> animationCmp;


            animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, RenderManager::instance().getWindow(),
                texture,
                8,
                16,
                false,
                4);
            animationCmp->addAnimation({
               {CowIdleRight, 3},
               {CowRunRight, 8},
               {CowSitDownAndUpRight, 7},
               {CowIdleSitRight, 3},
               {CowIdleSleepRight, 4},
               {CowIdleChewRight, 7},
               {CowIdleEatRight, 4},
               {CowIdleLoveRight, 6},
               {CowIdleLeft, 3},
               {CowRunLeft, 8},
               {CowSitDownAndUpLeft, 7},
               {CowIdleSitLeft, 3},
               {CowIdleSleepLeft, 4},
               {CowIdleChewLeft, 7},
               {CowIdleEatLeft, 4},
               {CowIdleLoveLeft, 6},
                });
        


       /* const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject,
            sf::FloatRect(gameObject->getPosition().x,
                gameObject->getPosition().y,
                object.getSize().x ,
                object.getSize().y ),
            false);
        gameObject->addComponent(boxCollider);*/
        // PhysicsManager::instance().addBoxCollisionCmp(boxCollider); 
        
        //gameObject->addComponent(std::make_shared<SteeringCmp>(*gameObject, sf::Vector2f(1.f, 1.f), animationCmp->getTextureRect().getSize().x/3, animationCmp->getTextureRect().getSize().y/3));
        gameObject->addComponent(std::make_shared<SteeringCmp>(*gameObject));
       // std::cout << animationCmp->getTextureRect().getSize().x << "SIzeY" << animationCmp->getTextureRect().getSize().y << std::endl;
        gameObject->addComponent(std::make_shared<CowAICmp>(*gameObject));
        animationCmp->init();        
        
        const auto& trigger = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(animationCmp->getTextureRect()), true);

        gameObject->addComponent(trigger);
        PhysicsManager::instance().addBoxCollisionCmp(trigger);
       
        animationCmp->init();



        RenderManager::instance().addCompToLayer(layer.getName(), animationCmp);
        gameObject->addComponent(animationCmp);

        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);

    }
    ;

     std::shared_ptr<GameObject>ObjectFactory::loadPlants(const tson::Layer& layer, std::shared_ptr<GameObject> patch, int index, std::string type, std::shared_ptr<sf::Texture> texture)
    {
        auto gameObject = std::make_shared<GameObject>(type + std::to_string(index));
        gameObject->setType(Plants);
        auto animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, RenderManager::instance().getWindow(),
            texture,
            7,
            13,
            false,
            3);
        animationCmp->addAnimation({
            {IdleDown , 4},
            {IdleLeft , 4},
            {IdleUp , 4},
            {MoveDown , 6},
            {MoveLeft , 6},
            {MoveUp , 6},
            {CryIdle , 4},
            {CryLeft , 4},
            {CryBack, 4},
            {ExplosionIdle, 7},
            {ExplosionLeft, 7},
            {ExplosionBack, 2},
            {Smoke, 6}, 
            });

        animationCmp->setCurrentAnimation(IdleDown);
        RenderManager::instance().addCompToLayer(layer.getName(), animationCmp);
        gameObject->addComponent(animationCmp);

        animationCmp->init();
        const auto& trigger = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(animationCmp->getTextureRect()), true);

        gameObject->addComponent(trigger);
        PhysicsManager::instance().addBoxCollisionCmp(trigger);

        gameObject->addComponent(std::make_shared<PlantCmp>(*gameObject)); 
        gameObject->addComponent(std::make_shared<PlantAICmp>(*gameObject, patch));

        auto hud = std::make_shared<PlantHudCmp>(*gameObject, RenderManager::instance().getWindow());
        RenderManager::instance().addCompToLayer(layer.getName(), hud);
        gameObject->addComponent(hud);

        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);

        m_patchPositions.push_back(sf::Vector2f(gameObject->getPosition().x, gameObject->getPosition().y));
        return gameObject;
    };


     void ObjectFactory::loadStaticCollider(tson::Object& object,
         const tson::Layer& layer)
     {
         auto gameObject = std::make_shared<GameObject>(object.getName());
         gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
        // gameObject->setType(ObjectType::StaticCollider);


         std::string id;


         float velocity{};
         float mass;

   /*      for (const auto* property : object.getProperties().get())
         {
             auto name = property->getName();

             if (name == "id")
             {
                 if ((id = property->getValue<std::string>()).length() > 0)
                 {

                     gameObject->setId(id);
                 }
             }
             else if (name == "mass")
             {
                 mass = property->getValue<float>();
             }
         }*/


         ////Collider
         //gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject,
         //    mass, sf::Vector2f(0.f, 0.f), gameObject->getPosition()));
         const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject,
             sf::FloatRect(gameObject->getPosition().x,
                 gameObject->getPosition().y,
                 object.getSize().x,
                 object.getSize().y),
             false);

         gameObject->addComponent(boxCollider);

         PhysicsManager::instance().addBoxCollisionCmp(boxCollider);

         gameObject->init();
         GameObjectManager::instance().addGameObject(gameObject);
     }

}

