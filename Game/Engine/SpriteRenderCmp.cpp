#pragma once
#include"pch.h"
#include"SpriteRenderCmp.h"
#include "GameObject.h"
namespace mmt_gd
{

	bool SpriteRenderCmp::init()
	{
		if (std::shared_ptr<sf::Texture> tempP = p_texture.lock()) //check if Texture is nullptr
		{
			sprite->setTexture(*tempP);
			return true;
		}
		return false;
	}

	void SpriteRenderCmp::update(float deltetime)
	{
		sprite->setPosition(gameObject.getPosition());
	}

	void SpriteRenderCmp::draw()
	{
		m_renderWindow.draw(*sprite);
	}
}