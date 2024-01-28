#pragma once
#pragma once 
#include "IRenderComponent.h"
#include "SpriteRenderCmp.h"
#include "AnimationTypes.h"
#include<map>

namespace mmt_gd
{
	class Sprite;
	class Texture;
	class GameObject;
	class SpriteAnimationCmp : public SpriteRenderCmp
	{
	public:
		SpriteAnimationCmp(
			GameObject& gameObject,
			sf::RenderWindow& renderWindow,
			std::weak_ptr<sf::Texture> p_texture,
			int TILING_X,
			int TILING_Y,
			bool vertical,
			float animationSpeed);

		~SpriteAnimationCmp() {};
		bool init() override;
		void update(float deltaTime) override;

		/**
		 * \brief 
		 *Add a animation row to the sprite
		 */
		void addAnimation(AnimationType animation, int frames);
		/**
		 * \brief
		 *Add animations to the sprite
		 */
		void addAnimation(std::vector<std::pair<AnimationType, int>> animations);

		void setCurrentAnimation(AnimationType animation)
		{
			if (m_animations[animation])
			{
				m_currentAnimation = animation;
			}
		};
		AnimationType getCurrentAnimation()
		{
			return m_currentAnimation;
		};

		int getCurrentAnimationIndex();
	protected:
		bool vertical;
		const int TILING_X;
		const int TILING_Y;
		float m_animationTime = 0;
		float m_animationSpeed;
		int m_animationFrame = 0;
		AnimationType m_currentAnimation = MoveRight;
		std::map<AnimationType, int> m_animations;
		std::vector<AnimationType> m_animationOrder;
	};
}