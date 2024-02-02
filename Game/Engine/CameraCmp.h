#pragma once
#include "IRenderComponent.h"
#include<memory>
namespace mmt_gd
{
	class CameraCmp : public IRenderComponent
	{
	public:
		CameraCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, sf::Vector2f size, float zoom)
			:IRenderComponent(gameObject, renderWindow), size(size), m_zoom(zoom) {};

		bool init() override;
		void update(float deltaTime) override;
		void draw() override;

		void rotate(float& degree);
		void zoom(float& zoom);
		void setSize(sf::Vector2f& size);
		void setViewPort(sf::FloatRect& viewPort);

		void setTarget(std::weak_ptr<GameObject> target);
		void screenShake() { isShaking = true; };
		
	protected:
		sf::Vector2f size;
		sf::View view;
		float shaking = 0;
		float m_zoom;
		bool isShaking = false;
		std::weak_ptr<GameObject> m_target;
	};
};