#pragma once
#include "PatchCmp.h"
#include "GameObject.h"
#include "pch.h"

namespace mmt_gd
{
	void PatchCmp::addPlant(std::weak_ptr<GameObject> plant)
	{
		if (std::shared_ptr<GameObject> tempP = plant.lock())
		{
			m_plants.push_back(plant);
			tempP->setPosition(gameObject.getPosition().x * m_plants.size(), gameObject.getPosition().y * m_plants.size());
		}
	};
	
}