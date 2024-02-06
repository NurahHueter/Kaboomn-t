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
		RenderManager::instance().getWindow().create({ 1920, 1080 }, "SFML Window", sf::Style::Fullscreen);
		//RenderManager::instance().getWindow().create({800, 800}, "SFML Window");
		InputManager::instance().setWindow(RenderManager::instance().getWindow());

		AssetManager::instance().LoadMusic("Axe", "../Engine/Assets/Sounds/axe-slash-1-106748.mp3");
		AssetManager::instance().LoadMusic("Pet", "../Engine/Assets/Sounds/seHm.mp3");
		AssetManager::instance().LoadMusic("Water", "../Engine/Assets/Sounds/splash-6213.mp3");
		AssetManager::instance().LoadMusic("BackGround", "../Engine/Assets/Sounds/8-bit-dream-land-142093.mp3");
		AssetManager::instance().LoadMusic("Cow", "../Engine/Assets/Sounds/animalhowling-107316.mp3");

		if (!AssetManager::instance().m_SoundBuffer["Explosion"])
		{
			AssetManager::instance().LoadSoundBuffer("Explosion", "../Engine/Assets/Sounds/hq-explosion-6288.mp3");
		}

		if (!AssetManager::instance().m_SoundBuffer["axe"])
		{
			AssetManager::instance().LoadSoundBuffer("axe", "../Engine/Assets/Sounds/axe-slash-1-106748.mp3");
		}
		if (!AssetManager::instance().m_SoundBuffer["pet"])
		{
			AssetManager::instance().LoadSoundBuffer("pet", "../Engine/Assets/Sounds/seHm.mp3");
		}
		if (!AssetManager::instance().m_SoundBuffer["water"])
		{
			AssetManager::instance().LoadSoundBuffer("water", "../Engine/Assets/Sounds/splash-6213.mp3");
		}
		if (!AssetManager::instance().m_SoundBuffer["cow"])
		{
			AssetManager::instance().LoadSoundBuffer("cow", "../Engine/Assets/Sounds/animalhowling-107316.mp3");
		}
		bindInput();

		GameStateManager::instance().addState("MenuState", std::make_shared<MenuState>());
		GameStateManager::instance().addState("PlayState", std::make_shared<PlayState>());
		GameStateManager::instance().addState("EndState", std::make_shared<EndState>());
		GameStateManager::instance().setState("MenuState");
		AssetManager::instance().m_Music["BackGround"]->play();
		AssetManager::instance().m_Music["BackGround"]->setLoop(true);
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
		auto plantObjects = GameObjectManager::instance().getObjectsByType(Plants);

		if (plantObjects.size() < 12 && m_isInGame)
		{

			
			GameStateManager::instance().setState("EndState");

			m_time = m_time + deltaTime;
			if (m_time > 10.f)
			{
				m_isInGame = false;
				m_time = 0;
				GameStateManager::instance().setState("MenuState");
			}
		}

		else if (InputManager::instance().isKeyUp("MenuState", 1))
		{
			GameStateManager::instance().setState("MenuState");
		}

		else if (InputManager::instance().isKeyUp("PlayState", 1))
		{
			m_isInGame = true;
			GameStateManager::instance().setState("PlayState");
		}

		else if (InputManager::instance().isKeyUp("EndState", 1) )
		{
			GameStateManager::instance().setState("EndState");
		}

		InputManager::instance().update();
		GameStateManager::instance().update(deltaTime);
	
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
				Game::~Game();
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
		}

		if (GameStateManager::instance().getCloseEvent())
		{
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
			InputManager::instance().bind("pet", sf::Keyboard::Key::E, 1);
			InputManager::instance().bind("res", sf::Keyboard::Key::R, 1);
			InputManager::instance().bind("leftclick", sf::Mouse::Left, 1);
			InputManager::instance().bind("debugdraw", sf::Keyboard::Key::Num0, 1);
			InputManager::instance().bind("space", sf::Keyboard::Key::Space, 1);
			InputManager::instance().bind("MenuState", sf::Keyboard::Key::Num1, 1);
			InputManager::instance().bind("PlayState", sf::Keyboard::Key::Enter, 1);
			InputManager::instance().bind("EndState", sf::Keyboard::Key::Num3, 1);
	}
}

