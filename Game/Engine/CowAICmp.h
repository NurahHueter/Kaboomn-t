#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{

	class CowAICmp : public IComponent
	{
	public:
		CowAICmp(GameObject& gameObject, float velocity)
			:IComponent(gameObject), m_velocity(velocity) {};
		bool init() override;
		void update(float deltaTime) override;


	private:
		float m_velocity;
	};
}