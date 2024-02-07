#include "pch.h"
#include "InputManager.h"


namespace mmt_gd
{
	void InputManager::update()
	{
		for (auto& kv : m_isKeyDown)
		{
			m_isKeyDown[kv.first] = false;
		}
		for (auto& kv : m_isKeyUp)
		{
			m_isKeyUp[kv.first] = false;
		}
		for (auto& kv : m_isMouseDown)
		{
			m_isMouseDown[kv.first] = false;
		}
		for (auto& kv : m_isMouseUp)
		{
			m_isMouseUp[kv.first] = false;
		}
	};

	bool InputManager::isKeyDown(int keyCode)
	{
		return m_isKeyDown.find(keyCode) != m_isKeyDown.end() ? m_isKeyDown[keyCode] : false;
	};

	bool InputManager::isKeyUp(int keyCode)
	{
		return m_isKeyUp.find(keyCode) != m_isKeyUp.end() ? m_isKeyUp[keyCode] : false;
	};
	bool InputManager::isKeyPressed(int keyCode)
	{
		return m_isKeyPressed.find(keyCode) != m_isKeyPressed.end() ? m_isKeyPressed[keyCode] : false;
	};


	bool InputManager::isKeyDown(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end()) // Check whether "action" is present in the dictionary
		{
			auto binding = m_bindings[action]; // `binding` contains the BindingForPlayer class
			return isKeyDown(binding.keyCode) && binding.playerIdx == playerIdx; // If yes, then call isKeyDown with the KeyCode and check if the playerIdx matches
		}

		return false;
	};

	bool InputManager::isKeyUp(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end())
		{
			auto binding = m_bindings[key];
			return isKeyUp(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};
	bool InputManager::isKeyPressed(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end())
		{
			auto binding = m_bindings[key];
			return isKeyPressed(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};

	//MouseInput
	bool InputManager::isMouseDown(int keyCode)
	{
		return m_isMouseDown.find(keyCode) != m_isMouseDown.end() ? m_isMouseDown[keyCode] : false;
	};

	bool InputManager::isMouseUp(int keyCode)
	{
		return m_isMouseUp.find(keyCode) != m_isMouseUp.end() ? m_isMouseUp[keyCode] : false;
	};
	bool InputManager::isMousePressed(int keyCode)
	{
		return m_isMousePressed.find(keyCode) != m_isMousePressed.end() ? m_isMousePressed[keyCode] : false;
	};


	bool InputManager::isMouseDown(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end())
		{
			auto binding = m_bindings[key]; 
			return isMouseDown(binding.keyCode) && binding.playerIdx == playerIdx; // If yes, then call isKeyDown with the KeyCode and check if the playerIdx matches
		}

		return false;
	};

	bool InputManager::isMouseUp(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end())
		{
			auto binding = m_bindings[key];
			return isMouseUp(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};
	bool InputManager::isMousePressed(const std::string& action, int playerIdx)
	{
		std::string key = action + std::to_string(playerIdx);
		if (m_bindings.find(key) != m_bindings.end())
		{
			auto binding = m_bindings[key];
			return isMousePressed(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};


	void InputManager::bind(const std::string& name, int keyCode, int playerIdx)
	{
		std::string key = name + std::to_string(playerIdx); //As the key, the name and the playerIdx are used so that the key is always unique

		m_bindings[key] = { keyCode, playerIdx }; // The two values are saved in the map. (BindingForPlayer)
	};

	void InputManager::unbind(const std::string& name, int playerIdx)
	{
		std::string key = name + std::to_string(playerIdx);
		auto binding_iterator = m_bindings.find(key); // If the entry is present, the binding iterator is an iterator that points to the value. Otherwise, it points to the end of the map.
		if (binding_iterator != m_bindings.end() && binding_iterator->second.playerIdx == playerIdx) // `second` is the second value in the map (BindingForPlayer)(keyCode, playerIdx)
		{
			m_bindings.erase(binding_iterator);
		}
	};

	void InputManager::handleEvents(sf::Event& event)
	{
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			m_isKeyDown[event.key.code] = true;
			m_isKeyPressed[event.key.code] = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased)
		{
			m_isKeyUp[event.key.code] = true;
			m_isKeyPressed[event.key.code] = false;
		}
		if (event.type == sf::Event::EventType::MouseButtonPressed)
		{
			m_isMouseDown[event.key.code] = true;
			m_isMousePressed[event.key.code] = true;
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased)
		{
			m_isMouseUp[event.key.code] = true;
			m_isMousePressed[event.key.code] = false;
		}
	}

	void InputManager::setWindow(sf::RenderWindow& window)
	{
		this->m_window.reset(&window, [](sf::RenderWindow*) {});
	}

	sf::Vector2f InputManager::getMousPosition()
	{
		if (m_window)
		{
			sf::Vector2f worldMousePosition = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			return worldMousePosition;
		}
	}
}