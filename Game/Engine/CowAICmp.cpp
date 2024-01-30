#include "pch.h"
#include "CowAICmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "GameObject.h"
#include "InputManager.h"

namespace mmt_gd
{
	bool CowAICmp::init()
	{
		gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleEatRight);
		return true;
	}

	void CowAICmp::update(float deltaTime)
	{
	}

}
