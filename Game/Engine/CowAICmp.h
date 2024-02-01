#pragma once
#include "IComponent.h"
#include<memory>
#include <SFML/System/Vector2.hpp>
namespace mmt_gd
{
	enum AIStateCow
	{
		Sleep,
		Attack,
		Despawn,
		Eat,ds
	};
	class PlantCmp;
	class CowAICmp : public IComponent
	{
	public:
		CowAICmp(GameObject& gameObject)
			:IComponent(gameObject) {};
		bool init() override;

		void update(float deltaTime) override;
		void attack();
		void despawn();
		void eat();
		void sleep();
		bool m_despawn = false;
		float m_rand = 0 ;

	private:
		AIStateCow currentState = Sleep;
		sf::Vector2f m_startPos;
	};
}