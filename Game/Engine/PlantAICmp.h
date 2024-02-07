/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
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
			:IComponent(gameObject), m_patch(patch) {};
		bool init() override;
		void update(float deltaTime) override;
		bool isExploding() const { return m_explosion; };
		void explode(float deltaTime);
		void happy(float deltaTime);

	private:
		AIState currentState = Happy;
		float m_timerIdle = 0.f;
		float m_timeIntervallIdle = 3.f;
		sf::Vector2f m_pointToGo = {};
		std::weak_ptr<GameObject> m_patch;
		bool m_isWalking = false;
		bool m_explosion = false;
		float m_interpolationSpeed = 2.f;
		sf::Vector2f m_direction = {};
		sf::Sound m_explosionSound;
	};
}