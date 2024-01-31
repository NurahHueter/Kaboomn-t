#include "pch.h"
#include "PlantAICmp.h"
#include "PlantCmp.h"
#include "GameObject.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "PatchCmp.h"
#include "VectorAlgebra2D.h"

namespace mmt_gd
{

	void PlantAICmp::update(float deltaTime)
	{
        auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        auto sanity = gameObject.getComponent<PlantCmp>()->getSanity();
		
		if (sanity > 50.f && currentState != Explode)
		{
			currentState = Happy;
		}
		else if(sanity < 50.f && currentState != Sad && currentState != Explode)
		{
			currentState = Sad;
			animationCmp->setCurrentAnimation(CryIdle);
		}
		else if (sanity <= 0.f && currentState != Explode)
		{
			currentState = Explode;
			animationCmp->setCurrentAnimation(ExplosionIdle);
		}


		switch (currentState)
		{
		case Happy:
			happy(deltaTime);
			break;
		case Explode:
			explode(deltaTime);
			break;
		case Envy:
			
			break;
		default:
			break;
		}
	};

	void PlantAICmp::explode(float deltaTime)
	{
		auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();
		auto frame = gameObject.getComponent<SpriteAnimationCmp>()->getCurrentFrameIndex();
		if (frame == 5)
		{
			animationCmp->setCurrentAnimation(Smoke);
		}
		if (animationCmp->getCurrentAnimation() == Smoke && frame == 4)
		{
			gameObject.markForDelete();
		}
	};

	void PlantAICmp::happy(float deltaTime)
	{
		auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();

		if (m_timerIdle == 0.f)
		{
			animationCmp->setCurrentAnimation(IdleLeft);
		}
		if (m_timerIdle > m_timeIntervallIdle && !m_isWalking)
		{
			m_isWalking = true;
			animationCmp->setCurrentAnimation(MoveDown);
			if (std::shared_ptr<GameObject> tempP = m_patch.lock())
			{
				const auto& bounds	= tempP->getComponent<PatchCmp>()->getBound();
				float randomX = bounds.left + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * bounds.width;
				float randomY = bounds.top + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * bounds.height;
				m_pointToGo = { randomX, randomY };
			}
			m_direction = MathUtil::unitVector(gameObject.getPosition() - m_pointToGo);

		}
		if (m_isWalking)
		{
			if (std::abs(MathUtil::length(gameObject.getPosition() - m_pointToGo)) < 5.f)
			{
				m_timerIdle = 0.f;
				m_isWalking = false;
			}

			gameObject.setPosition(gameObject.getPosition() + m_direction * 2.f * deltaTime);
		}

		m_timerIdle += deltaTime;
	}
}