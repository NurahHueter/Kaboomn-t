#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "CameraCmp.h"

namespace mmt_gd
{
    void EndState::init()
    {
        AssetManager::instance().LoadFont("font", "../Engine/Assets/Fonts/arial.ttf");
        m_score = PlayState::scoreClock.getElapsedTime().asSeconds();
    }

    void EndState::exit()
    {
        GameObjectManager::instance().shutdown();
    }

    void EndState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
    }

    void EndState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });
        sf::Text text;
        text.setFont(*AssetManager::instance().m_Font["font"]);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
       
        std::string instructions = "The game is over!\n"
            "You have survived for " + std::to_string(m_score) + " seconds\n\n\n"
            "Thank you for playing";
        
        text.setString(instructions);

        float x = (RenderManager::instance().getWindow().getSize().x - text.getGlobalBounds().width) / 2;
        float y = (RenderManager::instance().getWindow().getSize().y - text.getGlobalBounds().height) / 2;
        //Global
        text.setPosition(400, 400);
       
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}