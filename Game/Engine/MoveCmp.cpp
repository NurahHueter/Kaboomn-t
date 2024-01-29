#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "RigidBodyCmp.h"


namespace mmt_gd
{
    bool MoveCmp::init()
    {
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(IdleDown);
        return true;
    }
    void MoveCmp::update(float deltaTime)
    {

        sf::Vector2f velocity(0.0f, 0.0f);
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();

        if (InputManager::instance().isKeyPressed("up", gameObject.getPlayerIdx()))
        {
            velocity.y = -m_velocity;
            animation->setCurrentAnimation(MoveUp);
        }
        else if (InputManager::instance().isKeyPressed("down", gameObject.getPlayerIdx()))
        {
            velocity.y = m_velocity;
            animation->setCurrentAnimation(MoveDown);
        }

        else if (InputManager::instance().isKeyPressed("left", gameObject.getPlayerIdx()))
        {
            velocity.x = -m_velocity;
            animation->setCurrentAnimation(MoveLeft);
        }
        else if (InputManager::instance().isKeyPressed("right", gameObject.getPlayerIdx()))
        {
            velocity.x = m_velocity;
            animation->setCurrentAnimation(MoveRight);
        }
        else if (InputManager::instance().isKeyUp("up", gameObject.getPlayerIdx()))
        {
            animation->setCurrentAnimation(IdleUp);
        }
        else if (InputManager::instance().isKeyUp("down", gameObject.getPlayerIdx()))
        {
            animation->setCurrentAnimation(IdleDown);
        }
        else if (InputManager::instance().isKeyUp("left", gameObject.getPlayerIdx()))
        {
            animation->setCurrentAnimation(IdleLeft);
        }
        else if (InputManager::instance().isKeyUp("right", gameObject.getPlayerIdx()))
        {
            animation->setCurrentAnimation(IdleRight);
        }



        gameObject.setPosition(gameObject.getPosition() + velocity * deltaTime);

        //if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
      //{
      //    /*  rigidBodyCmp->setVelocityP(accVec * deltaTime);
      //      rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity()-(rigidBodyCmp->getVelocity()* 0.99f));
      //      rigidBodyCmp->setImpulse(accVec);
      //      sf::Vector2f velocity = rigidBodyCmp->getVelocity();
      //      velocity.x = std::min(std::abs(rigidBodyCmp->getVelocity().x), m_maxSpeed) * (velocity.x < 0 ? -1 : 1);
      //      velocity.y = std::min(std::abs(rigidBodyCmp->getVelocity().y), m_maxSpeed) * (velocity.y < 0 ? -1 : 1);
      //      rigidBodyCmp->setPosition(velocity, deltaTime);*/
      //}
       
    }
}
