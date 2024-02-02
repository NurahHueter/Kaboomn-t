#pragma once

#include "pch.h"
#include "GameState.h"
#include "Assetmanager.h"
#include "MapTile.h"
#include "GameObject.h"
#include "CameraCmp.h"
#include "SpriteRenderCmp.h"3

namespace mmt_gd
{
    void EndState::init()
    {
        AssetManager::instance().LoadTexture("background", "../Engine/Assets/endbg.png");
        
        auto goBg = std::make_shared<GameObject>("background");

        auto spriteCmp = std::make_shared<SpriteRenderCmp>(*goBg, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["background"]);
        spriteCmp->sprite->setScale(RenderManager::instance().getWindow().getSize().x / 2.f,
            RenderManager::instance().getWindow().getSize().y / 2.f);
        AssetManager::instance().LoadFont("font", "../Engine/Assets/Fonts/arial.ttf");
        m_score = PlayState::scoreClock.getElapsedTime().asSeconds();
        auto goCamera = std::make_shared<GameObject>("camera");
        auto cameraCmp = std::make_shared<CameraCmp>(*goCamera,
            RenderManager::instance().getWindow(),
            sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2.f,
                RenderManager::instance().getWindow().getSize().y / 2.f), 1.f);
        goCamera->addComponent(cameraCmp);
        goBg->addComponent(spriteCmp);
        RenderManager::instance().addLayer("hud2", 1, false);
        RenderManager::instance().addCompToLayer("hud2", spriteCmp);
        GameObjectManager::instance().addGameObject(goBg);
        RenderManager::instance().addCompToLayer("hud2", cameraCmp);
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

        // Hintergrund-Sprite zeichnen
        //sf::Sprite backgroundSprite(*AssetManager::instance().m_Textures["background"]);
        //RenderManager::instance().getWindow().draw(backgroundSprite);

        // Text zeichnen
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

        RenderManager::instance().getWindow().draw(text);

        RenderManager::instance().getWindow().display();
    }

}