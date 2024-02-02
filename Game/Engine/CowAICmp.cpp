#pragma once
#include "pch.h"
#include "CowAiCmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "GameObject.h"
#include "InputManager.h"
#include <random>
#include "SteeringCmp.h"
#include "PlantAICmp.h"
#include "PlantCmp.h"
#include "GameObjectManager.h"
#include "AssetManager.h"
namespace mmt_gd
{
    static sf::Clock movementClock;
    bool CowAICmp::init()
    {
        auto spriteAnimationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        spriteAnimationCmp->setCurrentAnimation(CowIdleSleepRight);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(15.0f, 35.0f);
        movementClock.restart();
        m_startPos = gameObject.getPosition();
        m_rand = distribution(gen);
        currentState = Sleep;
        return true;
    }

    void CowAICmp::update(float deltaTime)
    {
       

        if (movementClock.getElapsedTime().asSeconds() >= m_rand && 
            !gameObject.getComponent<SteeringCmp>()->m_astarStart)
        {
            AssetManager::instance().m_Music["Cow"]->play();
            gameObject.getComponent<SteeringCmp>()->init();
            gameObject.getComponent<SteeringCmp>()->m_astarStart = true;
            currentState = Attack;
        }

        if (m_despawn)
        {
            sf::Clock despawnTimer;
            gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
            m_despawn = false;
            gameObject.getComponent<SteeringCmp>()->m_astarStart = true;
            movementClock.restart();
            currentState = Despawn;
        }

        if (gameObject.getComponent<SteeringCmp>()->m_foundTarget)
        {
            gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
            currentState = Eat;       
        }

        switch (currentState)
        {
        case Sleep:
            sleep();
            break;
        case Attack:
            attack();
            break;
        case Eat:
            eat();
            break;
        case Despawn:
            despawn();
            break;
        default:
            break;
        };
    }

    void CowAICmp::attack()
    {
        auto steeringCmp = gameObject.getComponent<SteeringCmp>();
        steeringCmp->m_astarStart = true;
        steeringCmp->m_firstRun = true;
        gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
    }

    void CowAICmp::sleep()
    {
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleSleepLeft);
        gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
    }
    void CowAICmp::eat()
    {
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleChewRight);

    }
    void CowAICmp::despawn()
    {

        auto steeringCmp = gameObject.getComponent<SteeringCmp>();
        steeringCmp->m_astarStart = false;
        steeringCmp->m_firstRun = false;
        gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
        steeringCmp->clearPath();
        gameObject.setPosition(m_startPos);

        currentState = Sleep;
    }
  
}
