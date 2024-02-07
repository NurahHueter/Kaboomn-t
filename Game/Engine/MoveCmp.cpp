#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "ToolCmp.h"
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

        if (ToolCmp::m_usingTool == false)
        {
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

            else if (!InputManager::instance().isKeyPressed("right", gameObject.getPlayerIdx()) &&
                animation->getCurrentAnimation()==MoveRight)
            {
                animation->setCurrentAnimation(IdleRight);
            }
            else if (!InputManager::instance().isKeyPressed("left", gameObject.getPlayerIdx()) &&
                animation->getCurrentAnimation() == MoveLeft)
            {
                animation->setCurrentAnimation(IdleLeft);
            }
            else if (!InputManager::instance().isKeyPressed("up", gameObject.getPlayerIdx()) &&
                animation->getCurrentAnimation() == MoveUp)
            {
                animation->setCurrentAnimation(IdleUp);
            }
            else if (!InputManager::instance().isKeyPressed("down", gameObject.getPlayerIdx()) &&
                animation->getCurrentAnimation() == MoveDown)
            {
                animation->setCurrentAnimation(IdleDown);
            }
        }
        
        gameObject.setPosition(gameObject.getPosition() + velocity * deltaTime);
   
    }
}
