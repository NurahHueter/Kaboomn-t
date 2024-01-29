#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "ToolCmp.h"
#include "RigidBodyCmp.h"


namespace mmt_gd
{

    void ToolCmp::update(float deltaTime)
    {
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();
        if (InputManager::instance().isMouseDown("leftclick", gameObject.getPlayerIdx()))
        {

            animation->setCurrentAnimation(AxeHitDown);
        }
      

    }
}
