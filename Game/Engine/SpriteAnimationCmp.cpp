#pragma once
#include"pch.h"
#include"SpriteAnimationCmp.h"
#include"SpriteRenderCmp.h"
#include"AnimationTypes.h"
#include "GameObject.h"
namespace mmt_gd
{
	SpriteAnimationCmp::SpriteAnimationCmp(
		GameObject& gameObject,
		sf::RenderWindow& renderWindow,
		std::weak_ptr<sf::Texture> p_texture,
		const int TILING_X,
		const int TILING_Y,
		bool vertical,
		float animationSpeed)
		: SpriteRenderCmp(gameObject, renderWindow, p_texture),
		TILING_X(TILING_X), TILING_Y(TILING_Y), vertical(vertical), m_animationSpeed(animationSpeed){};

	bool SpriteAnimationCmp::init()
	{
		if (sprite)
		{
			if(std::shared_ptr<sf::Texture> tempP = p_texture.lock()) 
			{
				sprite->setTexture(*tempP);
				sprite->setTextureRect(sf::IntRect(0, 0, tempP->getSize().x / TILING_X, tempP->getSize().y / TILING_Y));				
			}
			else
			{
				return false;
			}
			return true;
		}
		return false;
	}

	void SpriteAnimationCmp::update(float deltaTime)
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
		sprite->setPosition(gameObject.getPosition());
	}

	void SpriteAnimationCmp::addAnimation(AnimationType animation, int frames)
	{
			m_animations[animation] = frames;
			m_animationOrder.push_back(animation);
	}
	void SpriteAnimationCmp::addAnimation(std::vector<std::pair<AnimationType, int>> animations)
	{
		for (auto& e : animations)
		{
			m_animations[e.first] = e.second;
			m_animationOrder.push_back(e.first);
		}
	};

	int SpriteAnimationCmp::getCurrentAnimationIndex() {
		auto it = std::find(m_animationOrder.begin(), m_animationOrder.end(), m_currentAnimation);
		if (it != m_animationOrder.end()) {
			return std::distance(m_animationOrder.begin(), it);
		}
		else {
			return -1; 
		}
	}
};
