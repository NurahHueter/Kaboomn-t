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
 
		for (auto icon : iconCmps)
		{
			if (icon->getIconType() == Love)
			{
				if (m_love >= 80 && m_love <= 100) {
					icon->setCurrentAnimation(Full);
				}
				else if (m_love >= 60 && m_love < 80) {
					icon->setCurrentAnimation(NearFull);
				}
				else if (m_love >= 40 && m_love < 60) {
					icon->setCurrentAnimation(Half);
				}
				else if (m_love >= 20 && m_love < 40) {
					icon->setCurrentAnimation(NearEmpty);
				}
				else if (m_love >= 0 && m_love < 20) {
					icon->setCurrentAnimation(Empty);
				}
			}
			if (icon->getIconType() == Sanity)
			{
				if (m_sanity >= 80 && m_sanity <= 100) {
					icon->setCurrentAnimation(Full);
				}
				else if (m_sanity >= 60 && m_sanity < 80) {
					icon->setCurrentAnimation(NearFull);
				}
				else if (m_sanity >= 40 && m_sanity < 60) {
					icon->setCurrentAnimation(Half);
				}
				else if (m_sanity >= 20 && m_sanity < 40) {
					icon->setCurrentAnimation(NearEmpty);
				}
				else if (m_sanity >= 0 && m_sanity < 20) {
					icon->setCurrentAnimation(Empty);
				}
			}
			if (icon->getIconType() == Water)
			{
				if (m_water >= 80 && m_water <= 100) {
					icon->setCurrentAnimation(Full);
				}
				else if (m_water >= 60 && m_water < 80) {
					icon->setCurrentAnimation(NearFull);
				}
				else if (m_water >= 40 && m_water < 60) {
					icon->setCurrentAnimation(Half);
				}
				else if (m_water >= 20 && m_water < 40) {
					icon->setCurrentAnimation(NearEmpty);
				}
				else if (m_sanity >= 0 && m_sanity < 20) {
					icon->setCurrentAnimation(Empty);
				}
			}
		}


	};
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