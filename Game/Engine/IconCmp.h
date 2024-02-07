/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
#pragma once 
#include "IRenderComponent.h"
#include "SpriteRenderCmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include<map>

namespace mmt_gd
{
	enum IconType
	{
		Sanity,
		Love,
		Water,
	};
	class Sprite;
	class Texture;
	class GameObject;
	class IconCmp : public SpriteAnimationCmp
	{
	public:
		IconCmp(
			GameObject& gameObject,
			sf::RenderWindow& renderWindow,
			std::weak_ptr<sf::Texture> p_texture,
			int TILING_X,
			int TILING_Y,
			bool vertical,
			float animationSpeed, IconType type
		) : SpriteAnimationCmp(gameObject, renderWindow, p_texture, TILING_X, TILING_Y, vertical, animationSpeed), m_type(type)
		{}
		void update(float deltaTime) override;
		void setPosition(sf::Vector2f position);
		IconType getIconType() const { return m_type; }

	protected:
		IconType m_type;
		sf::Vector2f m_position = { 1.f, 1.f };
	};
}