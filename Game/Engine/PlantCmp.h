#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "PlantTypes.h"

namespace mmt_gd
{

	class PlantCmp : public IComponent
	{
	public:
		PlantCmp(GameObject& gameObject)
			: IComponent(gameObject) {};
		bool init() { return true; };
		void update(float deltaTime) override;
		float getSanity() const { return m_sanity; };
		float getWater() const { return m_water; };
		float getAffection() const { return m_love; };

		void pet();
		void watering();
	private:
		PlantType m_type = PlantType::Green;
		float m_sanity = 100.f;
		float m_water = 100.f;
		float m_love = 100.f;
		const float M_MAXSANITY = 100.f;
		const float M_MAXWATER = 100.f;
		const float M_LOVE = 100.f;
	};

}
