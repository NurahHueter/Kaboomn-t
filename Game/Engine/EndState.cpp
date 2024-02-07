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
        AssetManager::instance().LoadTexture("endScreen", "../Engine/Assets/Endscreen.png");
        m_score = PlayState::scoreClock.getElapsedTime().asSeconds();

        sf::View view(sf::FloatRect(0, 0, RenderManager::instance().getWindow().getSize().x, RenderManager::instance().getWindow().getSize().y));
        RenderManager::instance().getWindow().setView(view);

        auto endscreen = std::make_shared<GameObject>("endScreen");
        auto endscreenCmp = std::make_shared<SpriteRenderCmp>(*endscreen, RenderManager::instance().getWindow(), AssetManager::instance().m_Textures["endScreen"]);
        endscreen->addComponent(endscreenCmp);
        endscreenCmp->sprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>(RenderManager::instance().getWindow().getSize().x), static_cast<int>(RenderManager::instance().getWindow().getSize().y)));
        endscreen->init();

        RenderManager::instance().addLayer("hud", 1, false);
        RenderManager::instance().addCompToLayer("hud", endscreenCmp);
        GameObjectManager::instance().addGameObject(endscreen);
    }

    void EndState::exit()
    {
        RenderManager::instance().shutdown();
        GameObjectManager::instance().shutdown();
		AssetManager::instance().shutdown();
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
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);

        std::string gameOverMessage = std::to_string(m_score);
        float xTextOffset = 50.f;
        float yTextOffset = 10.f;
        text.setString(gameOverMessage);
        float x = ((RenderManager::instance().getWindow().getView().getSize().x - text.getGlobalBounds().width) / 2) - xTextOffset;
        float y = ((RenderManager::instance().getWindow().getView().getSize().y - text.getGlobalBounds().height) / 2) + yTextOffset;
        text.setPosition(x, y);
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().getWindow().display();

    }
}