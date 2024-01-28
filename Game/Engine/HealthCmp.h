#pragma once
#include "IRenderComponent.h"
#include<memory>
namespace mmt_gd
{
	class HealthCmp : public IRenderComponent
	{
	public:
		HealthCmp(GameObject& gameObject, sf::RenderWindow& renderWindow,int health)
			:IRenderComponent(gameObject, renderWindow), m_health(health), m_currentHealth(health) {};
		bool init() override;
		void update(float deltaTime) override;
		void getDamage();
		void gainHealth();
		int getHealth() { return m_currentHealth; };
		void draw() override;

	protected:
		int m_health;
		int m_currentHealth;

		sf::RectangleShape m_background;
		sf::RectangleShape m_slider;
	};
}