#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace mmt_gd
{

    void GameStateManager::addState(std::string stateName, std::shared_ptr<GameState> state)
    {
        states[stateName] = state;
    };

    void GameStateManager::update(float delta) {
        if (currentState)
        {
            currentState->update(delta);
        }
    }

    void GameStateManager::draw() {
        if (currentState)
        {
            currentState->draw();
        }
    }

    void GameStateManager::setState(std::string stateName) {
        auto it = states.find(stateName);
        if (it != states.end()) {
            std::shared_ptr<GameState> state = it->second;

            if (state != currentState) {
                if (currentState != nullptr) {
                    currentState->exit();
                }
                currentState = state;
                currentState->init();
            }
        }
        else {
            // Handle the case where the stateName is not found in the states map.
            std::cerr << "Error: State '" << stateName << "' not found." << std::endl;
        }
    }

    std::shared_ptr<GameState> GameStateManager::getState()
    {

        return currentState;
    }

    void GameStateManager::CloseGame()
    {
        currentState->exit();
        states.clear();
        closeGame = true;
        AssetManager::instance().shutdown();
        InputManager::instance().shutdown();
        RenderManager::instance().shutdown();
        GameObjectManager::instance().shutdown();
    }
}
