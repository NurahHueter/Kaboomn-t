#include "pch.h"
#include "PatchCmp.h"
#include "GameObject.h"
#include "SpriteAnimationCmp.h"
#include "BoxCollisionCmp.h"


namespace mmt_gd
{
	void PatchCmp::addPlant(std::weak_ptr<GameObject> plant)
	{
		m_plants.push_back(plant);
	}

    bool PatchCmp::init()
    {
        const auto bounds = gameObject.getComponent<BoxCollisionCmp>();

        if (m_plants.empty()) {
            return false;
        }

        float smallRectWidth = bounds->m_shape.width / static_cast<float>(m_plants.size());
        float smallRectHeight = bounds->m_shape.height / static_cast<float>(m_plants.size());

        for (auto plant : m_plants)
        {
            if (std::shared_ptr<GameObject> tempP = plant.lock())
            {

                tempP->setPosition(gameObject.getPosition().x + smallRectWidth, gameObject.getPosition().y + smallRectHeight);
            }

        }

        return true;
    }
}