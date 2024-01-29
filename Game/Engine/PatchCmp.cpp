#include "pch.h"
#include "PatchCmp.h"
#include "GameObject.h"


namespace mmt_gd
{
	void PatchCmp::addPlant(std::shared_ptr<GameObject> plant)
	{
		m_plants.push_back(plant);

		plant->setPosition(gameObject.getPosition().x * m_plants.size(), gameObject.getPosition().y * m_plants.size());
	}
}