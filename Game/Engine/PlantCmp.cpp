#pragma once
#include "pch.h"
#include "PlantCmp.h"

namespace mmt_gd
{
	void PlantCmp::update(float deltaTime)
	{
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
				m_sanity += m_happy * deltaTime;
			}
		}

		if (m_getingEaten)
		{
			m_sanity -= 5.f * deltaTime ;
		}
		m_getingEaten = false;
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