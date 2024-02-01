#pragma once
#include "pch.h"
#include "CowAICmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "GameObject.h"
#include "InputManager.h"
#include <random>
#include "SteeringCmp.h"
#include "PlantAICmp.h"
#include "PlantCmp.h"
#include "GameObjectManager.h"
namespace mmt_gd
{
    bool CowAICmp::init()
    {
        auto spriteAnimationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        spriteAnimationCmp->setCurrentAnimation(CowIdleSleepRight);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(5.0f, 15.0f);

        m_startPos = gameObject.getPosition();
        m_rand = distribution(gen);
        currentState = Sleep;
        return true;
    }

    void CowAICmp::update(float deltaTime)
    {
        static sf::Clock movementClock;

        if (movementClock.getElapsedTime().asSeconds() >= m_rand && 
            !gameObject.getComponent<SteeringCmp>()->m_astarStart)
        {
            gameObject.getComponent<SteeringCmp>()->init();
            std::cout << "ATTACK" << std::endl;
            gameObject.getComponent<SteeringCmp>()->m_astarStart = true;
            currentState = Attack;
        }

        if (m_despawn)
        {
            std::cout << "DESPAWN" << std::endl;
            gameObject.getComponent<SteeringCmp>()->m_foundTarget = false;
            m_despawn = false;
            currentState = Despawn;
            
            movementClock.restart();
        }

        if (gameObject.getComponent<SteeringCmp>()->m_foundTarget)
        {
            std::cout << "Eat" << std::endl;
            currentState = Eat;
            gameObject.getComponent<SteeringCmp>()->m_foundTarget=false;
           
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
