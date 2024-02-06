#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "RenderManager.h"
#include "MapTile.h"
#include "PhysicsManager.h"

namespace mmt_gd
{
    class GameObject;
    class GameStateManager;
    class GameState
    {
    public:
        GameState(){};
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
    };


    
    class MenuState : public GameState
    {
    
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override; 

        sf::Vector2f m_textOriginalPosition;
    };
    class PlayState : public GameState
    {
    public:
        MapTile mapTile;
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override;

        static sf::Clock scoreClock;

    private:
        sf::Sound m_waterSound;
        sf::Sound m_axeSound;
        sf::Sound m_petSound;
        bool m_leftclickPressedPreviouslyTool = false;
        float m_radiusSquared = 1024.f;
        bool m_spaceKeyPressedPreviously = false;
    };
  
    class EndState : public GameState
    {
    public:
        MapTile mapTile;
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override;
    private:
        int m_score=0;
        float m_timer = 0;
    };
}
