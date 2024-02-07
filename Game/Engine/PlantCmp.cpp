/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
#include "pch.h"
#include "PlantCmp.h"
#include "IconCmp.h"

namespace mmt_gd
{
	void PlantCmp::update(float deltaTime)
	{
		sf::Clock getHarderClock;

		if (getHarderClock.getElapsedTime().asSeconds() >= 30)
		{
			m_lonelyness += 0.1f;
			m_dryingOut += 0.1f;
			getHarderClock.restart();
		}

		m_love -= m_lonelyness * deltaTime;
		m_water -= m_dryingOut * deltaTime;

		if (m_water < 60.f)
		{
			m_sanity  -= m_dryingOut * deltaTime;
		}
		if (m_love < 60.f)
		{
			m_sanity -= m_lonelyness * deltaTime;
		}

		if (m_water  > 60.f && m_love > 60.f)
		{
			if (m_sanity <= M_MAXSANITY)
			{
				isRegenerating = true;
				m_sanity += m_happy * deltaTime;
			}
		}
		else
		{
			isRegenerating = false;
		}

		if (m_getingEaten)
		{
			m_sanity -= 3.f * deltaTime ;
		}
		m_getingEaten = false;

		//Icons
		auto iconCmps = gameObject.getComponents<IconCmp>();
 
		for (auto icon : iconCmps) {
			switch (icon->getIconType()) {
			case Love:
				setIconAnimation(m_love, Love, icon);
				break;
			case Sanity:
				setIconAnimation(m_sanity, Sanity, icon);
				break;
			case Water:
				setIconAnimation(m_water, Water, icon);
				break;
			default:
				break;
			}
		}
	};

	void PlantCmp::setIconAnimation(float value, IconType iconType, std::shared_ptr<IconCmp> icon)
	{
		if (value >= 80 && value <= 100) {
			icon->setCurrentAnimation(Full);
		}
		else if (value >= 60 && value < 80) {
			icon->setCurrentAnimation(NearFull);
		}
		else if (value >= 40 && value < 60) {
			icon->setCurrentAnimation(Half);
		}
		else if (value >= 20 && value < 40) {
			icon->setCurrentAnimation(NearEmpty);
		}
		else if (value >= 0 && value < 20) {
			icon->setCurrentAnimation(Empty);
		}
	}

	void PlantCmp::pet()
	{
		m_love = M_LOVE;
	};
	void PlantCmp::watering()
	{
		m_water = M_LOVE;
	};

	void PlantCmp::getHitfromExplosion()
	{
		m_sanity -= 40.f;
	};
}