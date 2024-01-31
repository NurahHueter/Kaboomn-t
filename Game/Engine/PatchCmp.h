#pragma once
#include "IComponent.h"
#include "GameObject.h"

namespace mmt_gd
{

	class PatchCmp : public IComponent
	{
	public:
		PatchCmp(GameObject& gameObject, sf::FloatRect patchBounds)
			: IComponent(gameObject), m_patchBounds(patchBounds){};
		bool init() override;
		void update(float deltaTime){};
		void addPlant(std::weak_ptr<GameObject> plant);
		std::vector <std::weak_ptr<GameObject>> getPlants() { return m_plants; }
		sf::FloatRect getBound() const { return m_patchBounds; }

	private:
		std::vector<std::weak_ptr<GameObject>> m_plants;
		sf::FloatRect m_patchBounds;
	};
}