#include "pch.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "SteeringCmp.h"
#include "SpriteRenderCmp.h"
#include "CameraCmp.h"
#include "HealthCmp.h"
#include "ObjectTypes.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
#include"AnimationTypes.h"


namespace mmt_gd
{
    void ObjectFactory::processTsonObject(tson::Object& object, const tson::Layer& layer)
    {

        if (object.getType() == "SpaceShip")
        {
        }

    }
}

