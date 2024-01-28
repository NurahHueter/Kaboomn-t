#pragma once
#include <unordered_map>
namespace mmt_gd
{
    class IRenderComponent;

    struct RenderManager
    {
    public:
    
        static
            RenderManager&
            instance()
        {
            static RenderManager s;
            return s;
        }

        RenderManager(const RenderManager&) = delete;
        RenderManager& operator = (const RenderManager&) = delete;

        void setLayerOrder(std::string layer, int order);
        void addLayer(std::string layer, int order);
        void addCompToLayer(const std::string layer, std::weak_ptr<IRenderComponent> comp);

        sf::RenderWindow& getWindow() 
        {
            return m_window;  
        }

        void shutdown();
        void draw();

    private:
        RenderManager() {}
        ~RenderManager() {}

        sf::RenderWindow m_window; 
        std::map<std::string, std::vector<std::weak_ptr<IRenderComponent>>> m_CmpInLayer;
        std::vector<std::pair<std::string, int>> m_layers;
    };
}