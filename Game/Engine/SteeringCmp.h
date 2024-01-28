#pragma once
#include "IComponent.h"

#include<memory>
namespace mmt_gd
{
	class MapTile;
	class SteeringCmp : public IComponent
	{
	public:
		SteeringCmp(GameObject& gameObjectPlayer,  const sf::Vector2f& velocity, int sizeX,int sizeY)
			: IComponent(gameObjectPlayer),  m_velocity(velocity), m_sizeX(sizeX), m_sizeY(sizeY) {};
		bool init() override;
		void update(float deltaTime) override;
		void setTarget(sf::Vector2f target) { m_target = target; };
		bool reachedTarget() { return m_reachedTarget; };


	private:
		int m_sizeX;
		int m_sizeY;
		bool m_reachedTarget = false;
		sf::Vector2f nextTarget = { 0, 0 };
		sf::Vector2f m_target;
		sf::Vector2f m_velocity;
		sf::Vector2f direction = { 0.f, 0.f };
		std::vector<std::pair<int, int>> m_pathlist;
	};
}