#include "pch.h"
#include "IconCmp.h"
#include"SpriteAnimationCmp.h"
#include "GameObject.h"

namespace mmt_gd
{
	void IconCmp::setPosition(sf::Vector2f position)
	{
		m_position = position - gameObject.getPosition();
		sprite->setScale(sf::Vector2f(0.5f, 0.5f));
	}
	void IconCmp::update(float deltaTime)
	{

		m_animationTime += deltaTime * m_animationSpeed;
		m_animationFrame = (int)m_animationTime % m_animations[m_currentAnimation];

		int spriteOffsetX;
		int spriteOffsetY;
		if (vertical)
		{
			spriteOffsetX = getCurrentAnimationIndex() * sprite->getTextureRect().width;
			spriteOffsetY = m_animationFrame * sprite->getTextureRect().height;
		}
		else
		{
			spriteOffsetX = m_animationFrame * sprite->getTextureRect().width;
			spriteOffsetY = getCurrentAnimationIndex() * sprite->getTextureRect().height;
		}
			sprite->setTextureRect(sf::IntRect(
				spriteOffsetX,
				spriteOffsetY,
				sprite->getTextureRect().width,
				sprite->getTextureRect().height));

			sprite->setPosition(gameObject.getPosition() + m_position);
	}
};