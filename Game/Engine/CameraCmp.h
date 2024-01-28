#pragma once
#include "IRenderComponent.h"
#include<memory>
namespace mmt_gd
{
	class CameraCmp : public IRenderComponent
	{
	public:
		CameraCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, sf::Vector2f size)
			:IRenderComponent(gameObject, renderWindow), size(size) {};

		bool init() override;
		void update(float deltaTime) override;
		void draw() override;

		void rotate(float& degree);
		void zoom(float& zoom);
		void setSize(sf::Vector2f& size);
		void setViewPort(sf::FloatRect& viewPort);

		void setTarget(std::weak_ptr<GameObject> target);
		
	protected:
		sf::Vector2f size;
		sf::View view;

		std::weak_ptr<GameObject> m_target;
	};
};