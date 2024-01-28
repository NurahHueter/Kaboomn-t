#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "RigidBodyCmp.h"
namespace mmt_gd
{
    void MoveCmp::update(float deltaTime)
    {
        constexpr float acc = 690.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime

        sf::Vector2f accVec;
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();
        if (InputManager::instance().isKeyPressed("up", gameObject.getPlayerIdx()))
        {
            accVec = { 0.0f, -acc };
            animation->setCurrentAnimation(MoveUp);
        }
        if (InputManager::instance().isKeyPressed("down", gameObject.getPlayerIdx()))
        {
            accVec = { 0.0f, acc };
            animation->setCurrentAnimation(MoveDown);
        }
        if (InputManager::instance().isKeyPressed("left", gameObject.getPlayerIdx()))
        {
            accVec = { -acc, 0.0f };
            animation->setCurrentAnimation(MoveLeft);
        }
        if (InputManager::instance().isKeyPressed("right", gameObject.getPlayerIdx()))
        {
            accVec = { acc, 0.0f };
            animation->setCurrentAnimation(MoveRight);
        }
        
        if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
        {
            rigidBodyCmp->setVelocityP(accVec * deltaTime);
            rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity()-(rigidBodyCmp->getVelocity()* 0.99f));
            rigidBodyCmp->setImpulse(accVec);
            sf::Vector2f velocity = rigidBodyCmp->getVelocity();
            velocity.x = std::min(std::abs(rigidBodyCmp->getVelocity().x), m_maxSpeed) * (velocity.x < 0 ? -1 : 1);
            velocity.y = std::min(std::abs(rigidBodyCmp->getVelocity().y), m_maxSpeed) * (velocity.y < 0 ? -1 : 1);
            rigidBodyCmp->setPosition(velocity, deltaTime);
            gameObject.setPosition(rigidBodyCmp->getPosition());
        }
        
        // Reset acceleration 
        accVec = sf::Vector2f(0, 0);
    };
}