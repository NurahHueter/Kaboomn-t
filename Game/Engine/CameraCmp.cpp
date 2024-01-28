#pragma once
#include "pch.h"
#include "GameObject.h"
#include "CameraCmp.h"
namespace mmt_gd
{
	bool CameraCmp::init()
	{
		view.setSize(size);
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
			view.setCenter(tempP->getPosition());
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