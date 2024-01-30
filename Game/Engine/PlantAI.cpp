#include "pch.h"
#include "PlantAICmp.h"
#include "PlantCmp.h"
#include "GameObject.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"

namespace mmt_gd
{

	void PlantAICmp::update(float deltaTime)
	{
        auto animationCmp = gameObject.getComponent<SpriteAnimationCmp>();
        auto sanity = gameObject.getComponent<PlantCmp>()->getSanity();
		
		if (sanity > 50.f && currentState != Explode)
		{
			currentState = Happy;
			animationCmp->setCurrentAnimation(IdleLeft);
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
		//float randomX = m_respawnBounds.left + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m_respawnBounds.width;
		//float randomY = m_respawnBounds.top + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m_respawnBounds.height;
		//this->gameObject.setPosition(sf::Vector2f(randomX, randomY));
	}
}