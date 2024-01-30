#pragma once
#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "GameStateManager.h"
#include "GameState.h"

namespace mmt_gd
{

	void Game::Initialize()
	{
		RenderManager::instance().getWindow().setVerticalSyncEnabled(true);
		RenderManager::instance().getWindow().create({ 800, 640 }, "SFML Window");
		InputManager::instance().setWindow(RenderManager::instance().getWindow());

		bindInput();

		GameStateManager::instance().addState("MenuState", std::make_shared<MenuState>());
		GameStateManager::instance().addState("PlayState", std::make_shared<PlayState>());
		GameStateManager::instance().setState("MenuState");
	}

	void Game::Run()
	{
		Initialize();

		while (RenderManager::instance().getWindow().isOpen())
		{
			float deltaTime = m_clock.restart().asSeconds();
			HandleEvents();
			Update(deltaTime);
			GameStateManager::instance().draw();
		}
	};


	void Game::Update(float deltaTime)
	{

		if (InputManager::instance().isKeyUp("MenuState", 1))
		{
			GameStateManager::instance().setState("MenuState");
		}
		else if (InputManager::instance().isKeyUp("PlayState", 1))
		{
			GameStateManager::instance().setState("PlayState");
		}


		GameStateManager::instance().update(deltaTime);
		InputManager::instance().update();

		std::ostringstream ss;
		m_fps.update();
		ss << " | FPS: " << m_fps.getFps();

		RenderManager::instance().getWindow().setTitle(ss.str());
	}

	void Game::HandleEvents()
	{
		sf::Event event;
		while (RenderManager::instance().getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				GameStateManager::instance().CloseGame();
				RenderManager::instance().getWindow().close();
			}

			InputManager::instance().handleEvents(event);
			CloseGame(event.key);
		}
	};

	void Game::CloseGame(sf::Event::KeyEvent& e)
	{
		if (e.code == sf::Keyboard::Key::Escape)
		{
			GameStateManager::instance().CloseGame();
			RenderManager::instance().getWindow().close();
			Game::~Game();
		}
	};

	void Game::bindInput()
	{
			InputManager::instance().bind("up", sf::Keyboard::Key::W, 1);
			InputManager::instance().bind("down", sf::Keyboard::Key::S, 1);
			InputManager::instance().bind("left", sf::Keyboard::Key::A, 1);
			InputManager::instance().bind("right", sf::Keyboard::Key::D, 1);
			InputManager::instance().bind("leftclick", sf::Mouse::Left, 1);
			InputManager::instance().bind("debugdraw", sf::Keyboard::Key::Num0, 1);
			InputManager::instance().bind("space", sf::Keyboard::Key::Space, 1);
			InputManager::instance().bind("MenuState", sf::Keyboard::Key::Num1, 1);
			InputManager::instance().bind("PlayState", sf::Keyboard::Key::Num2, 1);
	}
}

