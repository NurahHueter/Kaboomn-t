#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"

namespace mmt_gd
{
    void MenuState::init()
    {
        AssetManager::instance().LoadFont("font","../Engine/Assets/Fonts/arial.ttf");
        auto goCamera = std::make_shared<GameObject>("camera");
        auto cameraCmp = std::make_shared<CameraCmp>(*goCamera,
            RenderManager::instance().getWindow(),
            sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2.f,
                RenderManager::instance().getWindow().getSize().y / 2.f), 1.25f);
        goCamera->addComponent(cameraCmp);
        RenderManager::instance().addLayer("hud", 1, false);
        RenderManager::instance().addCompToLayer("hud", cameraCmp);
        GameObjectManager::instance().addGameObject(goCamera);
    }

    void MenuState::exit()
    {
        GameObjectManager::instance().shutdown();
    }

    void MenuState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
    }

    void MenuState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });

        sf::Text text;
        text.setFont(*AssetManager::instance().m_Font["font"]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        
        std::string instructions =
            "Welcome to the ______ Game!\n\n"
            "Instructions:\n"
            "1. Press 'Enter' to start the game.\n"
            "2. Use 'E' to pet the animals.\n"
            "3. Press 'Space' to water the plants.\n"
            "4. Left-click to hit objects.\n"
            "5. Stand in front of the well and press 'Space' to fill up.\n\n"
            "Remember:\n"
            "   - Keep the plants alive by watering them.\n"
            "   - Show love to your animals by petting them.\n"
            "   - Use the well to replenish your resources.\n"
            "   - When 5 plants die, the game is over.\n"
            "Have fun farming!";


        text.setString(instructions);

        float x = (RenderManager::instance().getWindow().getView().getSize().x - text.getGlobalBounds().width) / 2;
        float y = (RenderManager::instance().getWindow().getView().getSize().y - text.getGlobalBounds().height) / 2;
        text.setPosition(x, y);
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}