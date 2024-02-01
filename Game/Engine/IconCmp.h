#pragma once 
#include "IRenderComponent.h"
#include "SpriteRenderCmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include<map>

namespace mmt_gd
{
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
			float animationSpeed
		) : SpriteAnimationCmp(gameObject, renderWindow, p_texture, TILING_X, TILING_Y, vertical, animationSpeed)
		{}
		void update(float deltaTime) override;
		void setPosition(sf::Vector2f position);
	protected:
		sf::Vector2f m_position = { 1.f, 1.f };
	};
}