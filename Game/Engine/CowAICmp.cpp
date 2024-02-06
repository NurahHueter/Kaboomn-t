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
    bool CowAICmp::m_isEating = false;
    static sf::Clock movementClock;
    bool CowAICmp::init()
    {
        movementClock.restart();
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleSleepRight);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(15.0f, 35.0f);
        m_rand = distribution(gen);

        m_startPos = gameObject.getPosition();
        currentState = Sleep;
        m_cowSound.setBuffer(*AssetManager::instance().m_SoundBuffer["cow"]);
        return true;
    }

    void CowAICmp::update(float deltaTime)
    {
        auto steeringCmp = gameObject.getComponent<SteeringCmp>();

        if (movementClock.getElapsedTime().asSeconds() >= m_rand && 
            !steeringCmp->m_astarStart)
        {
            m_cowSound.play();
            steeringCmp->init();
            steeringCmp->m_astarStart = true;
            currentState = Attack;
        }

        if (m_despawn)
        {
            sf::Clock despawnTimer;
            steeringCmp->m_foundTarget = false;
            steeringCmp->m_astarStart = true;
            m_despawn = false;
            movementClock.restart();
            currentState = Despawn;
        }

        if (steeringCmp->m_foundTarget)
        {
            steeringCmp->m_foundTarget = false;
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

        m_isEating = false;
        steeringCmp->m_astarStart = true;
        steeringCmp->m_firstRun = true;

        gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
    }

    void CowAICmp::sleep()
    {
        m_isEating = false;
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleSleepLeft);
        gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
    }

    void CowAICmp::eat()
    {
        m_isEating = true;
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleChewRight);
    }

    void CowAICmp::despawn()
    {
        auto steeringCmp = gameObject.getComponent<SteeringCmp>();

        m_isEating = false;
        steeringCmp->m_astarStart = false;
        steeringCmp->m_firstRun = false;
        steeringCmp->m_foundTarget = false;
        steeringCmp->clearPath();

        gameObject.setPosition(m_startPos);
        currentState = Sleep;
    }
  
}
