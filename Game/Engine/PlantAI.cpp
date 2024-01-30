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
		
		if (sanity > 50.f && currentState != Happy)
		{
			currentState = Happy;
			animationCmp->setCurrentAnimation(IdleDown);
		}
		else if(sanity < 50.f && currentState != Sad && currentState != Explode)
		{
			currentState = Sad;
			animationCmp->setCurrentAnimation(MoveUp);
		}
		else if (sanity <= 0.f && currentState != Explode)
		{
			currentState = Explode;
			animationCmp->setCurrentAnimation(ExplosionIdle);
		}


		switch (currentState)
		{
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
}