#pragma once
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
        if (InputManager::instance().isMouseDown("leftclick", 1) && !m_usingTool)
        {
            m_usingTool = true;
            AssetManager::instance().m_Music["Axe"]->play();
            animation->setCurrentFrameIndex(0);
            //reset the current animation cycle to index 0 so it always starts at 0
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


        //WATER
        else if (InputManager::instance().isKeyPressed("space", 1) 
            && !m_usingTool 
            && gameObject.getComponent<WaterNotiCmp>()->m_waterAmount>0)
        {
            AssetManager::instance().m_Music["Water"]->play();
            gameObject.getComponent<WaterNotiCmp>()->looseWater();
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
