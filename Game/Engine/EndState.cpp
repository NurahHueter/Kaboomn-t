#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"
#include "SpriteRenderCmp.h"
#include "GameStateManager.h"

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
        m_timer += deltaTime;
        if (m_timer > 7.f)
        {
            m_timer = 0;
            GameStateManager::instance().setState("MenuState");
        }
    }

    void EndState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });
        sf::Text text;
        text.setFont(*AssetManager::instance().m_Font["font"]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        std::string gameOverMessage = "Game Over!\n"
            "Survival Time: " + std::to_string(m_score) + " seconds!\n\n"
            "Thank you for playing!\n"
            "Feel free to try again and aim for an even longer survival time!";

        text.setString(gameOverMessage);
        float x = (RenderManager::instance().getWindow().getView().getSize().x - text.getGlobalBounds().width) / 2;
        float y = (RenderManager::instance().getWindow().getView().getSize().y - text.getGlobalBounds().height) / 2;
        text.setPosition(x, y);
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}