#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"

namespace mmt_gd
{
    void MenuState::init()
    {
        AssetManager::instance().LoadFont("font","../Engine/Assets/SpaceShip/arial.ttf");
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
        text.setString("Press 2 to start the game, press 1 to come back tp Startscreen");
        text.setCharacterSize(24); 
        text.setFillColor(sf::Color::White);

        float x = (RenderManager::instance().getWindow().getSize().x - text.getGlobalBounds().width) / 2;
        float y = (RenderManager::instance().getWindow().getSize().y - text.getGlobalBounds().height) / 2;
        text.setPosition(x, y);
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();
    }
}