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
		PlantAICmp(GameObject& gameObject, std::weak_ptr<GameObject> patch)
			:IComponent(gameObject), m_patch(patch){};
		bool init() override { return true; };
		void update(float deltaTime) override;
		void explode(float deltaTime);
		void happy(float deltaTime);

	private:
		AIState currentState = Happy;
		float m_timerIdle = 0.f;
		float m_timeIntervallIdle = 5.f;
		sf::Vector2f m_pointToGo = {};
		std::weak_ptr<GameObject> m_patch;
		bool m_isWalking = false;
		float m_interpolationSpeed = 2.f;
		sf::Vector2f m_direction = {};
	};
}