#pragma once
#include "IComponent.h"
#include "GameObject.h"

namespace mmt_gd
{

	class PatchCmp : public IComponent
	{
	public:
		PatchCmp(GameObject& gameObject)
			: IComponent(gameObject) {};
		bool init() override { return true; };
		void update(float deltaTime){};
		void addPlant(std::shared_ptr<GameObject> plant);

	private:
		std::vector<std::shared_ptr<GameObject>> m_plants;
	};
}