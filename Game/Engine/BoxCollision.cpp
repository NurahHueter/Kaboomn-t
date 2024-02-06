#pragma once
#include "pch.h"
#include "BoxCollisionCmp.h"
#include "GameObject.h"
#include "IComponent.h"
#include "RigidBodyCmp.h"
#include "PhysicsManager.h"
#include "MoveCmp.h"
#include "SpriteAnimationCmp.h"

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
		if ( gameObject.getType() == Player)
		{

			m_shape = sf::FloatRect(gameObject.getPosition() + 
				sf::Vector2f(
					gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().height/3, 
					gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().width/3),
					m_shape.getSize());
		}
		else if (gameObject.getType() == Cow)
		{
			m_shape = sf::FloatRect(gameObject.getPosition() -
				sf::Vector2f(
					gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().height / 4,
					gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().width / 4),
				m_shape.getSize());
		}

		else
		{
			m_shape = sf::FloatRect(gameObject.getPosition(), m_shape.getSize());
		}
		
	}
}