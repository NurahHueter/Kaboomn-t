#pragma once
#include "IComponent.h"

#include<memory>
namespace mmt_gd
{
	class MapTile;
	class SteeringCmp : public IComponent
	{
	public:
		SteeringCmp(GameObject& gameObjectPlayer)
			: IComponent(gameObjectPlayer) {};
		bool init() override;
		void update(float deltaTime) override;
		void setTarget(sf::Vector2f target) { m_target = target; };
		bool reachedTarget() { return m_reachedTarget; };
		

	private:
		
		bool m_reachedTarget = false;
		sf::Vector2f nextTarget = { 0, 0 };
		sf::Vector2f m_target;
		sf::Vector2f m_velocity;
		sf::Vector2f direction = { 0.f, 0.f };
		std::vector<std::pair<int, int>> m_pathlist;
	};
}