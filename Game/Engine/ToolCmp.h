/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
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
		int m_waterAmount = 5;
		bool m_spaceKeyPressedPreviouslyTool = false;
		bool m_leftclickPressedPreviouslyTool = false;
	};
}