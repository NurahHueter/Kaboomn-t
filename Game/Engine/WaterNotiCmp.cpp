#pragma
#include "pch.h"
#include "WaterNotiCmp.h"
#include "GameObject.h"
#include "RigidBodyCmp.h"
#include "InputManager.h"
#include "ToolCmp.h"

namespace mmt_gd
{
	bool WaterNotiCmp::init()
	{ 
		m_background.setSize(sf::Vector2f(15.f, 3.f));
		m_background.setFillColor(sf::Color(30, 30, 30, 200)); 
		m_slider.setSize(sf::Vector2f(15.f, 2.f));
		m_slider.setFillColor(sf::Color(0x00, 0x82, 0xfc));
		return true;
	};
	void WaterNotiCmp::update(float deltaTime)
	{
		float sliderWidth = (float)m_waterAmount / m_maxwaterAmount * m_background.getSize().x;
		m_slider.setSize(sf::Vector2f(sliderWidth, m_slider.getSize().y)); 

		m_background.setPosition(gameObject.getPosition().x+8.f, gameObject.getPosition().y+8.f);
		m_slider.setPosition(gameObject.getPosition().x+8.f, gameObject.getPosition().y+8.f );
	};

	void WaterNotiCmp::addWater()
	{
		m_waterAmount = m_maxwaterAmount;
	}
	void WaterNotiCmp::looseWater()
	{
		if (m_waterAmount > 0)
		{
			m_waterAmount--;
		}
	
	}
	;
	void WaterNotiCmp::draw()
	{
		m_renderWindow.draw(m_background);
		m_renderWindow.draw(m_slider);
	};
}