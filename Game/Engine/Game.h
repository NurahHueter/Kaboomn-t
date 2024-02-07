/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
#pragma once
#include "FPS.h"
namespace mmt_gd
{
	class Game
	{
	public:
		void Run();

	private:
		void Initialize();
		void bindInput();
		void Update(float deltaTime);
		void HandleEvents();
		void CloseGame(sf::Event::KeyEvent& e);
		bool m_isInGame = false;
		static sf::Clock m_score;
		float m_time = 0;
		sf::Clock m_clock;
		Fps m_fps;
	};
}