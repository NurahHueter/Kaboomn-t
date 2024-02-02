#pragma once
#include "IRenderComponent.h"
#include<memory>
namespace mmt_gd
{
	class PlantHudCmp : public IRenderComponent
	{
	public:
		PlantHudCmp(GameObject& gameObject, sf::RenderWindow& renderWindow)
			:IRenderComponent(gameObject, renderWindow) {};
		bool init() override;
		void update(float deltaTime) override;
		void draw() override;

	};
}