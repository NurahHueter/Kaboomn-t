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
#include "ObjectTypes.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
#include"AnimationTypes.h"


namespace mmt_gd
{
    void ObjectFactory::processTsonObject(tson::Object& object, const tson::Layer& layer)
    {
        
        if (object.getType() == "Player")
        {
            loadPlayer(object, layer);
        }
    }

    void ObjectFactory::loadPlayer(tson::Object& object, const tson::Layer& layer)
    {

        auto gameObject = std::make_shared<GameObject>(object.getName());
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
        //gameObject->setType(ObjectType::Spaceship);
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
        animationCmp->init();
        RenderManager::instance().addCompToLayer(layer.getName(), animationCmp);
        gameObject->addComponent(animationCmp);

        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);
    }
}

