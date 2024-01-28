#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

namespace mmt_gd
{
    class GameState; // forward declaration to avoid circular header file dependency

    class GameStateManager
    {
    public:
        static GameStateManager& instance() {
            static GameStateManager s;
            return s;
        }

        GameStateManager(const GameStateManager&) = delete;
        GameStateManager& operator=(const GameStateManager&) = delete;

        GameStateManager() : currentState(nullptr) {}

        void update(float deltaTime);
        void draw();
        void addState(std::string stateName,std::shared_ptr<GameState> state);
        void setState(std::string stateName);
        void CloseGame();

    private:
        ~GameStateManager() {}
        std::map<std::string, std::shared_ptr<GameState>> states;
        std::shared_ptr<GameState> currentState;
    };
}