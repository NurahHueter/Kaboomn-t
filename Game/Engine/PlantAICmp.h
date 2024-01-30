#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	enum AIState
	{
		Happy,
		Sad,
		Envy,
		Explode
	};
	class PlantAICmp : public IComponent
	{
	public:
		PlantAICmp(GameObject& gameObject)
			:IComponent(gameObject) {};
		bool init() override { return true; };
		void update(float deltaTime) override;
		void explode(float deltaTime);

	private:
		AIState currentState = Happy;
	};
}