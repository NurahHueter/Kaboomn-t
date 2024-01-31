#pragma
#include "pch.h"
#include "PlantHud.h"
#include "GameObject.h"
#include "PlantCmp.h"
#include "AssetManager.h"

namespace mmt_gd
{
	bool PlantHudCmp::init()
	{
		AssetManager::instance().LoadFont("font", "../Engine/Assets/Fonts/arial.ttf");
		//m_love.setFont(*AssetManager::instance().m_Font["font"]);

		//m_love.setFillColor(sf::Color::Red);

		//m_water.setFont(*AssetManager::instance().m_Font["font"]);
		//m_water.setFillColor(sf::Color::Blue);

		//m_sanity.setFont(*AssetManager::instance().m_Font["font"]);
		//m_sanity.setFillColor(sf::Color::Yellow);

		return true;
	};
	void PlantHudCmp::update(float deltaTime)
	{
		/*const auto plantCmp = gameObject.getComponent<PlantCmp>();*/
		//m_sanity.setString(std::to_string(plantCmp->getSanity()));
		//m_water.setString(std::to_string(plantCmp->getWater()));
		//m_love.setString(std::to_string(plantCmp->getAffection()));
		//m_sanity.setPosition(gameObject.getPosition());
		//m_water.setPosition(gameObject.getPosition().x + 5, gameObject.getPosition().y);
		//m_love.setPosition(gameObject.getPosition().x + 10, gameObject.getPosition().y);
	};

	void PlantHudCmp::draw()
	{
		const auto plantCmp = gameObject.getComponent<PlantCmp>();
		sf::Text m_love;
		m_love.setString(std::to_string(static_cast<int>(plantCmp->getAffection())));
		m_love.setCharacterSize(10);
		m_love.setFont(*AssetManager::instance().m_Font["font"]);
		m_love.setPosition(gameObject.getPosition().x , gameObject.getPosition().y + 10);
		m_love.setFillColor(sf::Color::Red);

		sf::Text m_water;
		m_water.setString(std::to_string(static_cast<int>(plantCmp->getWater())));
		m_water.setCharacterSize(10);
		m_water.setFont(*AssetManager::instance().m_Font["font"]);
		m_water.setPosition(gameObject.getPosition().x, gameObject.getPosition().y + 5);
		m_water.setFillColor(sf::Color::Blue);

		sf::Text m_sanity;
		m_sanity.setString(std::to_string(static_cast<int>(plantCmp->getSanity())));
		m_sanity.setCharacterSize(10);
		m_sanity.setFont(*AssetManager::instance().m_Font["font"]);
		m_sanity.setPosition(gameObject.getPosition());
		m_sanity.setFillColor(sf::Color::Black);



		m_renderWindow.draw(m_love);
		m_renderWindow.draw(m_sanity);
		m_renderWindow.draw(m_water);
	};
}