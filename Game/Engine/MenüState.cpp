#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"
#include "Inputmanager.h"
#include "SpriteRenderCmp.h"
#include "GameStateManager.h"

namespace mmt_gd
{
    void MenuState::init()
    {
        AssetManager::instance().LoadFont("font","../Engine/Assets/Fonts/arial.ttf");
        AssetManager::instance().LoadTexture("startScreen", "../Engine/Assets/Startscreen2.png");
        AssetManager::instance().LoadTexture("exitButtonB", "../Engine/Assets/Exit.png");
        AssetManager::instance().LoadTexture("startButton", "../Engine/Assets/Play.png");

        sf::View view(sf::FloatRect(0, 0, RenderManager::instance().getWindow().getSize().x, RenderManager::instance().getWindow().getSize().y));
        RenderManager::instance().getWindow().setView(view);

        auto startscreen = std::make_shared<GameObject>("Startscreen");
        auto startscreenCmp = std::make_shared<SpriteRenderCmp>(*startscreen, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["startScreen"]);
        startscreen->addComponent(startscreenCmp);
        startscreenCmp->sprite->setTextureRect(sf::IntRect(0,0,static_cast<int>(RenderManager::instance().getWindow().getSize().x) , static_cast<int>(RenderManager::instance().getWindow().getSize().y) ));
            startscreen->init();
      
        //start
        auto startGo = std::make_shared<GameObject>("StartButton");
        auto startCmp = std::make_shared<SpriteRenderCmp>(*startGo, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["startButton"]);
        startGo->addComponent(startCmp);
        startGo->init();

        startGo->setPosition(350.f, 400.f);
  
        //exit
        auto exitGo = std::make_shared<GameObject>("ExitButton");
        auto exitCmp = std::make_shared<SpriteRenderCmp>(*exitGo, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["exitButtonB"]);
        exitGo->addComponent(exitCmp);
        exitGo->init();
        exitGo->setPosition(350.f, 650.f);
        

        RenderManager::instance().addLayer("hud", 1, false);
        RenderManager::instance().addCompToLayer("hud", startscreenCmp);
        RenderManager::instance().addCompToLayer("hud", startCmp);
        RenderManager::instance().addCompToLayer("hud", exitCmp);
        GameObjectManager::instance().addGameObject(startscreen);
        GameObjectManager::instance().addGameObject(startGo);
        GameObjectManager::instance().addGameObject(exitGo);

        GameObjectManager::instance().init();
    }

    void MenuState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void MenuState::update(float deltaTime)
    {
       
        if (GameObjectManager::instance().getGameObject("ExitButton"))
        {
            auto exitButton = GameObjectManager::instance().getGameObject("ExitButton")->getComponent<SpriteRenderCmp>()->sprite->getGlobalBounds();
            
            if (exitButton.contains(InputManager::instance().getMousPosition()) &&
                InputManager::instance().isMousePressed("leftclick", 1))
            {
                GameStateManager::instance().CloseGame();
            }

        }
        if (GameObjectManager::instance().getGameObject("StartButton"))
        {
            auto startButton = GameObjectManager::instance().getGameObject("StartButton")->getComponent<SpriteRenderCmp>()->sprite->getGlobalBounds();
            if (startButton.contains(InputManager::instance().getMousPosition()) &&
                InputManager::instance().isMousePressed("leftclick", 1))
            {
                GameStateManager::instance().setState("PlayState");
            }

        }

        
        GameObjectManager::instance().update(deltaTime);

    }

    void MenuState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().display();
    }
}