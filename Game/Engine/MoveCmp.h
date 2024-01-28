#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	class MoveCmp : public IComponent
	{
	public:
		MoveCmp(GameObject& gameObject, sf::Vector2f velocity)
			:IComponent(gameObject), m_velocity(velocity){};
		bool init() override { return true; };
		void update(float deltaTime) override;
		
		
	private:
		float m_maxSpeed = 500.f;
		sf::Vector2f m_velocity;
		sf::Vector2f direction = {0.f, 0.f};
	};
}