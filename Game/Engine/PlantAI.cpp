/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah H�ter, Florian Rauter
*/
#include "pch.h"
#include "PlantAICmp.h"
#include "PlantCmp.h"
#include "GameObject.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "CameraCmp.h"
#include "IconCmp.h"

#include "PatchCmp.h"
#include "VectorAlgebra2D.h"

namespace mmt_gd
{
	bool PlantAICmp::init()
	{
		
		m_explosionSound.setBuffer(*AssetManager::instance().m_SoundBuffer["Explosion"]);
		return true;
	};
	void PlantAICmp::update(float deltaTime)
	{
        auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        auto sanity = gameObject.getComponent<PlantCmp>()->getSanity();
		
		if ((sanity > 50.f || gameObject.getComponent<PlantCmp>()->isRegenarating()) && currentState != Explode)
		{
			currentState = Happy;
		}
		else if((sanity < 50.f || !gameObject.getComponent<PlantCmp>()->isRegenarating()) && currentState != Sad && currentState != Explode)
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
		if (m_explosion)
		{
			GameObjectManager::instance().getGameObject("Player")->getComponent<CameraCmp>()->screenShake();
			m_explosionSound.play();
			m_explosion = false;
		}
		if (frame == 5)
		{
			animationCmp->setCurrentAnimation(Smoke);
			m_explosion = true;
		}
		if (animationCmp->getCurrentAnimation() == Smoke && frame == 4)
		{
			gameObject.markForDelete();
		}
	};

	void PlantAICmp::happy(float deltaTime)
	{
		auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();
		sf::Vector2f plantOrigin = gameObject.getMiddle();

		if (m_timerIdle == 0.f)
		{
			animationCmp->setCurrentAnimation(IdleDown);
		}

		m_timerIdle += deltaTime;

		if (m_timerIdle > m_timeIntervallIdle && !m_isWalking)
		{
			m_isWalking = true;
			animationCmp->setCurrentAnimation(MoveDown);

			if (std::shared_ptr<GameObject> tempP = m_patch.lock())
			{
				const auto& bounds = tempP->getComponent<PatchCmp>()->getBound();
				float randomX = bounds.left + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * bounds.width;
				float randomY = bounds.top + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * bounds.height;
				m_pointToGo = { randomX, randomY };
			}

			m_direction = MathUtil::unitVector(m_pointToGo - gameObject.getMiddle());
		}

		if (m_isWalking)
		{
			float distance = MathUtil::length(gameObject.getMiddle() - m_pointToGo);

			if (distance < 2.f)
			{
				m_timerIdle = 0.f;
				m_isWalking = false;
			}

			sf::Vector2f newPosition = MathUtil::lerp(gameObject.getMiddle(), m_pointToGo, deltaTime);
			gameObject.setPosition(newPosition.x - animationCmp->getTextureRect().width / 2.f, newPosition.y - animationCmp->getTextureRect().height / 2.f);
		}
	}
} 