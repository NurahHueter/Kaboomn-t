#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{

	class MoveCmp : public IComponent
	{
	public:
		MoveCmp(GameObject& gameObject, float velocity)
			:IComponent(gameObject), m_velocity(velocity){};
		bool init() override;
		void update(float deltaTime) override;
		
		
	private:
		float m_velocity;
	};
}