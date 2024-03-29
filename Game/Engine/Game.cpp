/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah H�ter, Florian Rauter
*/
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
		RenderManager::instance().getWindow().create({ 1920, 1080 }, "Kaboomn't", sf::Style::Fullscreen);
		InputManager::instance().setWindow(RenderManager::instance().getWindow());

		bindInput();

		// Load a custom cursor image
		sf::Texture cursorTexture;
		if (!cursorTexture.loadFromFile("../Engine/Assets/CatpawMouseScale.png"))
		{
			return;
		}

		// Set the cursor image as the mouse cursor
		sf::Cursor customCursor;
		customCursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });

		RenderManager::instance().getWindow().setMouseCursorVisible(true); 
		RenderManager::instance().getWindow().setMouseCursor(customCursor);

		GameStateManager::instance().addState("MenuState", std::make_shared<MenuState>());
		GameStateManager::instance().addState("PlayState", std::make_shared<PlayState>());
		GameStateManager::instance().addState("EndState", std::make_shared<EndState>());
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

		//if (InputManager::instance().isKeyUp("MenuState", 1))
		//{
		//	GameStateManager::instance().setState("MenuState");
		//}

		//if (InputManager::instance().isKeyUp("PlayState", 1))
		//{
		//	GameStateManager::instance().setState("PlayState");
		//}

		//if (InputManager::instance().isKeyUp("EndState", 1) )
		//{
		//	GameStateManager::instance().setState("EndState");
		//}

		InputManager::instance().update();
		GameStateManager::instance().update(deltaTime);
	
		//std::ostringstream ss;
		//m_fps.update();
		//ss << " | FPS: " << m_fps.getFps();

		//RenderManager::instance().getWindow().setTitle(ss.str());
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
			InputManager::instance().bind("Esc", sf::Keyboard::Key::Escape, 1);
	}
}

