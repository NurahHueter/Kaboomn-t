#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "PlantTypes.h"

namespace mmt_gd
{

	class PlantCmp : public IComponent
	{
	public:
		PlantCmp(GameObject& gameObject, PlantType type)
			: IComponent(gameObject) {};
		bool init() { return true; };
		void update(float deltaTime) {};
		float getSanity() const { return sanity; };
		float getWater() const { return water; };
		float getAffection() const { return love; };

		void pet() {};
		void watering() {};
	private:
		PlantType m_type = PlantType::Green;
		float sanity = 300.f;
		float water = 300.f;
		float love = 300.f;
	};

}
