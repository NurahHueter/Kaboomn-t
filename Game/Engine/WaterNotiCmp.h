#pragma once
#include "IRenderComponent.h"
#include<memory>
#include <SFML/Graphics/RectangleShape.hpp>
namespace mmt_gd
{
	class WaterNotiCmp : public IRenderComponent
	{
	public:
		WaterNotiCmp(GameObject& gameObject, sf::RenderWindow& renderWindow,int maxwaterAmount)
			:IRenderComponent(gameObject, renderWindow), m_maxwaterAmount(maxwaterAmount), m_waterAmount(maxwaterAmount) {};
		bool init() override;
		void update(float deltaTime) override;
		int getHealth() const { return m_maxwaterAmount; };
		void addWater();
		void looseWater();
		void draw() override;
		int m_maxwaterAmount;
		int m_waterAmount;
	protected:
		
		float m_Xoffset = 16.f;
		float m_Yoffset = 8.f;
		sf::RectangleShape m_background;
		sf::RectangleShape m_slider;
	};
}