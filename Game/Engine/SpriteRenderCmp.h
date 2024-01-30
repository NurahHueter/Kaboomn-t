#pragma once
#include "IRenderComponent.h"
#include<memory>


namespace mmt_gd
{
	class Sprite;
	class Texture;
	class GameObject;
	class SpriteRenderCmp : public IRenderComponent
	{
	public:
		SpriteRenderCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, std::weak_ptr<sf::Texture> p_texture)
			: IRenderComponent(gameObject, renderWindow), p_texture(p_texture) {};
		~SpriteRenderCmp() {};
		void mirror(bool mirror) { m_mirror = mirror;};
		bool init() override;
		void update(float deltaTime) override;
		void draw() override;

		sf::IntRect getTextureRect()
		{
			return sprite->getTextureRect();
		}
	protected:
		bool m_mirror = false;
		std::weak_ptr<sf::Texture> p_texture;
		std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	};
}

                                                                                         \
