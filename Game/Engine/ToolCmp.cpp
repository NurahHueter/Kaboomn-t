#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "ToolCmp.h"
#include "ToolCmp.h"
#include "RigidBodyCmp.h"


namespace mmt_gd
{
    bool ToolCmp::m_usingTool = false;

    void ToolCmp::update(float deltaTime)
    {
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();


        //AXE
        if (InputManager::instance().isMouseDown("leftclick", gameObject.getPlayerIdx()))
        {
            m_usingTool = true;
            //animation->setCurrentFrameIndex(0);
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
            
        }



        else if (InputManager::instance().isKeyDown("space", gameObject.getPlayerIdx()))
        {
            m_usingTool = true;
            //animation->setCurrentFrameIndex(0);
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

        }




        if (animation->getCurrentAnimation() == AxeHitRight && animation->getCurrentFrameIndex() == 7)
        {
            m_usingTool = false;
            animation->setCurrentAnimation(IdleRight);
        }
        else if (animation->getCurrentAnimation() == AxeHitLeft && animation->getCurrentFrameIndex() == 7)
        {
            m_usingTool = false;
            animation->setCurrentAnimation(IdleLeft);
        }
        else if (animation->getCurrentAnimation() == AxeHitUp && animation->getCurrentFrameIndex() == 7)
        {
            m_usingTool = false;
            animation->setCurrentAnimation(IdleUp);
        }
        else if (animation->getCurrentAnimation() == AxeHitDown && animation->getCurrentFrameIndex() == 7)
        {
            m_usingTool = false;
            animation->setCurrentAnimation(IdleDown);
        }
      
    }
}
