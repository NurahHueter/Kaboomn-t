#include "pch.h"
#include "PatchCmp.h"
#include "GameObject.h"
#include "SpriteAnimationCmp.h"
#include "BoxCollisionCmp.h"


namespace mmt_gd
{
	void PatchCmp::addPlant(std::shared_ptr<GameObject> plant)
	{
		m_plants.push_back(plant);
	}

    bool PatchCmp::init()
    {
        const auto bounds = gameObject.getComponent<BoxCollisionCmp>();

        if (m_plants.empty()) {
            return false;
        }

        // Beachten Sie, dass die Größe der kleinen Rechtecke durch m_plants.size() geteilt wird
        float smallRectWidth = bounds->m_shape.width / static_cast<float>(m_plants.size());
        float smallRectHeight = bounds->m_shape.height / static_cast<float>(m_plants.size());

        for (int i = 0; i < m_plants.size(); i++)
        {
            float centerX;
            float centerY;

            if (i % 2 == 0)
            {
                centerX = bounds->m_shape.left + (i / 2) * smallRectWidth + smallRectWidth / 2;
                centerY = bounds->m_shape.top + smallRectHeight / 2;
            }
            else
            {
                centerX = bounds->m_shape.left + ((i - 1) / 2) * smallRectWidth + smallRectWidth / 2;
                centerY = bounds->m_shape.top + smallRectHeight * 2.5f;
            }

           const auto spriteBounds = m_plants[i]->getComponent<SpriteAnimationCmp>()->getTextureRect();
           float spriteCenterX = spriteBounds.width / 2.0f;
           float spriteCenterY = spriteBounds.height / 2.0f;

           m_plants[i]->setPosition(centerX + spriteCenterX, centerY + spriteCenterY);
        }

        return true;
    }
}