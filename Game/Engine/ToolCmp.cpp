#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "ToolCmp.h"
#include "ToolCmp.h"
#include "RigidBodyCmp.h"
#include "WaterNotiCmp.h"
#include "AssetManager.h"


namespace mmt_gd
{
    bool ToolCmp::m_usingTool = false;

    void ToolCmp::update(float deltaTime)
    {
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();


        //AXE
        if (InputManager::instance().isMousePressed("leftclick", 1)  && !m_leftclickPressedPreviouslyTool &&!m_usingTool)
        {
  
            
                m_usingTool = true;

                animation->setCurrentFrameIndex(0);
                animation->setCurrentAnimationTime(0);

                if (animation->getCurrentAnimation() == IdleDown || animation->getCurrentAnimation() == MoveDown)
                {
                    animation->setCurrentAnimation(AxeHitDown);
                }
                else if (animation->getCurrentAnimation() == IdleUp || animation->getCurrentAnimation() == MoveUp)
                {
                    animation->setCurrentAnimation(AxeHitUp);
                }
                else if (animation->getCurrentAnimation() == IdleLeft || animation->getCurrentAnimation() == MoveLeft)
                {
                    animation->setCurrentAnimation(AxeHitLeft);
                }
                else if (animation->getCurrentAnimation() == IdleRight || animation->getCurrentAnimation() == MoveRight)
                {
                    animation->setCurrentAnimation(AxeHitRight);
                }
                m_leftclickPressedPreviouslyTool = true;
        }
        else if (!InputManager::instance().isMousePressed("leftclick", 1))
        {
            m_leftclickPressedPreviouslyTool = false;
        }


        //WATER
        if (InputManager::instance().isKeyPressed("space", 1) &&
            !m_usingTool &&
            gameObject.getComponent<WaterNotiCmp>()->m_waterAmount > 0 && !m_spaceKeyPressedPreviouslyTool)
        {
            
                m_usingTool = true;
                animation->setCurrentFrameIndex(0);
                animation->setCurrentAnimationTime(0);

                if (animation->getCurrentAnimation() == IdleDown || animation->getCurrentAnimation() == MoveDown)
                {
                    animation->setCurrentAnimation(WaterDown);
                }
                else if (animation->getCurrentAnimation() == IdleUp || animation->getCurrentAnimation() == MoveUp)
                {
                    animation->setCurrentAnimation(WaterUp);
                }
                else if (animation->getCurrentAnimation() == IdleLeft || animation->getCurrentAnimation() == MoveLeft)
                {
                    animation->setCurrentAnimation(WaterLeft);
                }
                else if (animation->getCurrentAnimation() == IdleRight || animation->getCurrentAnimation() == MoveRight)
                {
                    animation->setCurrentAnimation(WaterRight);
                }
            

            m_spaceKeyPressedPreviouslyTool = true;
        }
        else if (!InputManager::instance().isKeyPressed("space", 1))
        {
            m_spaceKeyPressedPreviouslyTool = false;
        }


        if (animation->getCurrentFrameIndex() == 7)
        {
            if (animation->getCurrentAnimation() == AxeHitRight || animation->getCurrentAnimation() == WaterRight)
            {
                m_usingTool = false;
                animation->setCurrentAnimation(IdleRight);
            }
            else if (animation->getCurrentAnimation() == AxeHitLeft || animation->getCurrentAnimation() == WaterLeft)
            {
                m_usingTool = false;
                animation->setCurrentAnimation(IdleLeft);
            }
            else if (animation->getCurrentAnimation() == AxeHitUp || animation->getCurrentAnimation() == WaterUp)
            {
                m_usingTool = false;
                animation->setCurrentAnimation(IdleUp);
            }
            else if (animation->getCurrentAnimation() == AxeHitDown || animation->getCurrentAnimation() == WaterDown)
            {
                m_usingTool = false;
                animation->setCurrentAnimation(IdleDown);
            }
        }
    }
}
