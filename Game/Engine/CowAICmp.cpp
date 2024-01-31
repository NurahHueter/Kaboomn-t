#pragma once
#include "pch.h"
#include "CowAICmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "GameObject.h"
#include "InputManager.h"
#include <random>
#include "SteeringCmp.h"

namespace mmt_gd
{
    bool CowAICmp::init()
    {
        auto spriteAnimationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        spriteAnimationCmp->setCurrentAnimation(CowIdleSleepRight);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(15.0f, 35.0f);

        m_startPos = gameObject.getPosition();
        m_rand = distribution(gen);

        return true;
    }

    void CowAICmp::update(float deltaTime)
    {
        static sf::Clock movementClock;

        if (movementClock.getElapsedTime().asSeconds() >= m_rand && !gameObject.getComponent<SteeringCmp>()->m_astarStart)
        {
            currentState = Attack;
        }

        if (m_despawn)
        {
            currentState = Despawn;
            m_despawn = false;
            movementClock.restart();
        }

        switch (currentState)
        {
        case Sleep:
            sleep();
            break;
        case Attack:
            attack();
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
    }

    void CowAICmp::sleep()
    {
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleSleepLeft);
    }

    void CowAICmp::despawn()
    {
        auto steeringCmp = gameObject.getComponent<SteeringCmp>();
        steeringCmp->m_astarStart = false;
        steeringCmp->m_firstRun = false;

        steeringCmp->clearPath();
        gameObject.setPosition(m_startPos);
        steeringCmp->init();

        currentState = Sleep;
    }
}
