#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"
#include "SpriteRenderCmp.h"

namespace mmt_gd
{
    void MenuState::init()
    {


        AssetManager::instance().LoadFont("font","../Engine/Assets/Fonts/arial.ttf");
        AssetManager::instance().LoadTexture("startScreen", "../Engine/Assets/Startscreen2.png");
        AssetManager::instance().LoadTexture("exitButtonB", "../Engine/Assets/Exit.png");
        AssetManager::instance().LoadTexture("startButton", "../Engine/Assets/Play.png");

        auto startscreen = std::make_shared<GameObject>("Startscreen");
        auto startscreenCmp = std::make_shared<SpriteRenderCmp>(*startscreen, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["startScreen"]);
        startscreen->addComponent(startscreenCmp);
        startscreenCmp->sprite->setTextureRect(sf::IntRect(0,0,static_cast<int>(RenderManager::instance().getWindow().getSize().x) , static_cast<int>(RenderManager::instance().getWindow().getSize().y) ));
            startscreen->init();

        startscreenCmp->sprite->setScale(2.f, 2.f);

        //start
        auto startGo = std::make_shared<GameObject>("Start");
        auto startCmp = std::make_shared<SpriteRenderCmp>(*startGo, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["startButton"]);
        startGo->addComponent(startCmp);
        startGo->init();

        startGo->setPosition(800.f, 850.f);
        startCmp->sprite->setScale(1.5f, 1.5f);
        startscreenCmp->sprite->setScale(2.f, 2.f);

        //exit
        auto exitGo = std::make_shared<GameObject>("ExitB");
        auto exitCmp = std::make_shared<SpriteRenderCmp>(*exitGo, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["exitButtonB"]);
        exitGo->addComponent(exitCmp);
        exitGo->init();
        exitCmp->sprite->setScale(1.5f, 1.5f);
        exitGo->setPosition(800.f, 1200.f);
        

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
    }

    void MenuState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
        //sf::View view = RenderManager::instance().getWindow().getDefaultView();
        //RenderManager::instance().getWindow().setView(view);

    }

    void MenuState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });

        //sf::Text text;
        //text.setFont(*AssetManager::instance().m_Font["font"]);
        //text.setCharacterSize(24);
        //text.setFillColor(sf::Color::White);
        //
        //std::string instructions =
        //    "Welcome to the Kaboomn't Game! (work in progress)\n\n"
        //    "Instructions:\n"
        //    "1. Press 'Enter' to start the game.\n"
        //    "2. Press 'ESC' to close the game.\n"
        //    "3. Use 'E' to pet the plants.\n"
        //    "4. Press 'Space' to water the plants.\n"
        //    "5. Left-click to hit the cows.\n\n"
        //    "Remember:\n"
        //    "   - Keep the plants alive by watering them.\n"
        //    "   - Stand in front of the well and press 'Space' to fill up.\n"
        //    "   - Show love to your animals by petting them.\n"
        //    "   - Use the well to replenish your resources.\n"
        //    "   - When 5 plants die, the game is over.\n"
        //    "Have fun farming!";


        //text.setString(instructions);

        //float x = (RenderManager::instance().getWindow().getView().getSize().x - text.getGlobalBounds().width) / 2;
        //float y = (RenderManager::instance().getWindow().getView().getSize().y - text.getGlobalBounds().height) / 2;
        /*text.setPosition(x, y);*/
        RenderManager::instance().draw();
        /*RenderManager::instance().getWindow().draw(text);*/
        RenderManager::instance().getWindow().display();

    }
}