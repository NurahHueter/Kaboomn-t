#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"

namespace mmt_gd
{
    void EndState::init()
    {
        AssetManager::instance().LoadFont("font", "../Engine/Assets/Fonts/arial.ttf");
        m_score = PlayState::scoreClock.getElapsedTime().asSeconds();
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
        text.setPosition(300, 400);
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}