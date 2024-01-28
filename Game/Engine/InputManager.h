#pragma once
#include <map>
namespace mmt_gd
{
    struct InputManager
    {
        static
            InputManager&
            instance()
        {
            static InputManager s;
            return s;
        } // instance

        InputManager(const InputManager&) = delete;
        InputManager& operator = (const InputManager&) = delete;

        void update();

        bool isKeyDown(int keyCode);
        bool isKeyUp(int keyCode);
        bool isKeyPressed(int keyCode);


        bool isKeyDown(const std::string& action, int playerIdx);
        bool isKeyUp(const std::string& action, int playerIdx);
        bool isKeyPressed(const std::string& action, int playerIdx);

        bool isMouseDown(int keyCode);
        bool isMouseUp(int keyCode);
        bool isMousePressed(int keyCode);


        bool isMouseDown(const std::string& action, int playerIdx);
        bool isMouseUp(const std::string& action, int playerIdx);
        bool isMousePressed(const std::string& action, int playerIdx);

        sf::Vector2f getMousPosition();

        void bind(const std::string& name, int keyCode, int playerIdx);
        void unbind(const std::string& name, int playerIdx);

        void handleEvents(sf::Event& event);

        void setWindow(sf::RenderWindow& window);

    private:
        std::shared_ptr<sf::RenderWindow> m_window;

        std::map<int, bool> m_isKeyDown{};
        std::map<int, bool> m_isKeyPressed{};
        std::map<int, bool> m_isKeyUp{};

        std::map<int, bool> m_isMouseDown{};
        std::map<int, bool> m_isMousePressed{};
        std::map<int, bool> m_isMouseUp{};

        class BindingForPlayer {
        public:
            int keyCode;
            int playerIdx;
        };


        std::map<std::string, BindingForPlayer> m_bindings{};                //(action), (keyCode,playerIdx)

        InputManager() {}
        ~InputManager() {}
    };
}
