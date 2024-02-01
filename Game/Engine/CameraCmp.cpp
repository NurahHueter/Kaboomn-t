#pragma once
#include "pch.h"
#include "GameObject.h"
#include "SpriteAnimationCmp.h"
#include "CameraCmp.h"
namespace mmt_gd
{
	bool CameraCmp::init()
	{
		view.setSize(size);
		view.zoom(0.28f);
		return true;
	}
	void CameraCmp::setTarget(std::weak_ptr<GameObject> target)
	{
		m_target = target;
	};
	void CameraCmp::update(float deltaTime)
	{
		if (std::shared_ptr<GameObject> tempP = m_target.lock())
		{
			auto textureRect = tempP->getComponent<SpriteAnimationCmp>()->getTextureRect();
			view.setCenter(tempP->getPosition().x + textureRect.width / 2.f, tempP->getPosition().y + textureRect.height / 2.f);
		}

		if (isShaking)
		{
			float shakeOffsetX = (rand() % 11) - 5.f;
			float shakeOffsetY = (rand() % 11) - 5.f;
			view.move(shakeOffsetX, shakeOffsetY);
			shaking += 1.f * deltaTime;

			if (shaking > 1.5)
			{
				shaking = 0;
				isShaking = false;
			}
				
		}
	}

	void CameraCmp::draw()
	{
		m_renderWindow.setView(view);
	};

	void CameraCmp::rotate(float& degree)
	{
		view.rotate(degree);
	};

	void CameraCmp::zoom(float& zoom)
	{
		view.rotate(zoom);
	};

	void CameraCmp::setSize(sf::Vector2f& size)
	{
		view.setSize(size);
	};

	void CameraCmp::setViewPort(sf::FloatRect& viewPort)
	{
		view.setViewport(viewPort);
	};
}