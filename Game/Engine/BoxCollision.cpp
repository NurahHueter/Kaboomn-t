#pragma once
#include "pch.h"
#include "BoxCollisionCmp.h"
#include "GameObject.h"
#include "IComponent.h"
#include "RigidBodyCmp.h"
#include "PhysicsManager.h"
#include "MoveCmp.h"

namespace mmt_gd
{
	bool BoxCollisionCmp::init()
	{
		if (gameObject.getComponent<RigidBodyCmp>())
		{
			rigidBody = gameObject.getComponent<RigidBodyCmp>();
		}
		
		return true;
	}
	void BoxCollisionCmp::update(float deltaTime)
	{
		//calibration PlayerBoundingbox
		if (gameObject.getComponent<MoveCmp>())
		{
			m_shape = sf::FloatRect(gameObject.getPosition() + sf::Vector2f(16, 16), m_shape.getSize());
		}
		else
		{
			m_shape = sf::FloatRect(gameObject.getPosition(), m_shape.getSize());
		}
		
	}
}