#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	class ToolCmp : public IComponent
	{
	public:
		ToolCmp(GameObject& gameObject)
			:IComponent(gameObject) {};
		bool init() override { return true; };
		void update(float deltaTime) override;
		static bool m_usingTool;

	};
}