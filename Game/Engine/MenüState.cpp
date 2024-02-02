#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"

namespace mmt_gd
{
    void MenuState::init()
    {
        AssetManager::instance().LoadFont("font","../Engine/Assets/Fonts/arial.ttf");  
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
        

        std::string instructions = "Press 2 to start the game\n"
            "E -> pet\n"
            "Space -> watering\n"
            "LeftMouse -> hit\n"
            "Space in Front of the Well -> fill up\n\n\n"
            "Keep the Plants alive, care for the cows";

        text.setString(instructions);

        float x = (RenderManager::instance().getWindow().getSize().x - text.getGlobalBounds().width) / 2;
        float y = (RenderManager::instance().getWindow().getSize().y - text.getGlobalBounds().height) / 2;
        text.setPosition(x, y);

        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}