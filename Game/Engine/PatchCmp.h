#pragma once
#include "IComponent.h"

namespace mmt_gd
{

	class PatchCmp : public IComponent
	{
	public:
		PatchCmp(GameObject& gameObjectPlayer)
			: IComponent(gameObjectPlayer) {};
		bool init() {};
		void update(float deltaTime) {};
		void addPlant(std::weak_ptr<GameObject> plant);

	private:
		std::vector<std::weak_ptr<GameObject>> m_plants;
	};
}