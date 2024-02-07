#include "pch.h"
#include "PatchCmp.h"
#include "PlantCmp.h"
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
                tempP->setPosition(gameObject.getPosition().x + smallRectWidth, 
                    gameObject.getPosition().y + smallRectHeight);
            }

        }

        return true;
    }
    void PatchCmp::update(float deltaTime)
    {
       std::vector<std::weak_ptr<GameObject>> tempPlants;

       for (auto plant : m_plants)
       {
           if (plant.lock())
           {
               tempPlants.push_back(plant);
           }
           else
           {
               for (auto plantLonely : m_plants)
               {
                   if (std::shared_ptr<GameObject> tempP = plantLonely.lock())
                   {
                       tempP->getComponent<PlantCmp>()->friendDied();
                   }
               }
           }
       }

       m_plants = tempPlants;
    };
}