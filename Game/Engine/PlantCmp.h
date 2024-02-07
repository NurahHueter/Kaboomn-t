/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "PlantTypes.h"
#include "IconCmp.h"

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
		void setIconAnimation(float value, IconType iconType, std::shared_ptr<IconCmp> icon);

		void cowAttack(bool getingEaten) { m_getingEaten = getingEaten; };
		void getHitfromExplosion();
		void friendDied() { m_lonelyness += 0.5f; };
		bool isRegenarating() const { return isRegenerating; }

		void pet();
		void watering();

	private:
		PlantType m_type = PlantType::Green;
		float m_sanity = 100.f;
		float m_water = 100.f;
		float m_love = 100.f;

		float m_lonelyness = 1.1f;
		float m_dryingOut = 1.1f;

		float m_happy = 2.0f;
		bool isRegenerating = false;
		bool m_getingEaten = false;
		const float M_MAXSANITY = 100.f;
		const float M_MAXWATER = 100.f;
		const float M_LOVE = 100.f;
	};

}
