#include "pch.h"
#include "PlantCmp.h"

namespace mmt_gd
{
	void PlantCmp::update(float deltaTime)
	{
		m_love -= 1.f * deltaTime;
		m_sanity -= 10.f * deltaTime;
		m_water -= 1.f * deltaTime;

		if (m_water < 60.f)
		{
			m_sanity --;
		}
		if (m_love < 60.f)
		{
			m_sanity--;
		}

		if ((m_water && m_love) > 60.f)
		{
			if (m_sanity <= M_MAXSANITY)
			{
				m_sanity++;
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
}