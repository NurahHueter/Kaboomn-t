#pragma once
#include "pch.h"
#include "RenderManager.h"
#include "IRenderComponent.h"
#include "GameObject.h"

namespace mmt_gd
{
    void RenderManager::setLayerOrder(std::string layer, int order)
    {
        auto it = std::find_if(m_layers.begin(), m_layers.end(),
            [layer](const auto& element) { return element.first == layer; });

        if (it != m_layers.end())
        {
            it->second = order;
        }
        else
        {
            std::cerr << "Layer '" << layer << "' does not exist." << std::endl;
        }
    };

    void RenderManager::addLayer(std::string layer, int order)
    {
        auto it = std::find_if(m_layers.begin(), m_layers.end(),
            [layer](const auto& element) { return element.first == layer; });

        if (it != m_layers.end())
        {
            std::cerr << "Layer '" << layer << "' already exists" << std::endl;
            return;
        }

        m_layers.emplace_back(layer, order);
        m_CmpInLayer.insert({ layer, std::vector<std::weak_ptr<IRenderComponent>>{} });
    };

    void RenderManager::addCompToLayer(const std::string layer, std::weak_ptr<IRenderComponent> comp)
    {
        auto it = std::find_if(m_layers.begin(), m_layers.end(),
            [layer](const auto& element) { return element.first == layer; });

        if (it != m_layers.end())
        {
            m_CmpInLayer[layer].push_back(comp);
        }
        else
        {
            std::cerr << "Layer '" << layer << "' Does not exist '" << std::endl;
        }
    }

    void RenderManager::shutdown()
    {
        m_layers.clear();
        m_CmpInLayer.clear();
    }

    void RenderManager::draw()
    {
        std::sort(m_layers.begin(), m_layers.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

        for (auto& layer : m_layers)
        {
            for (auto& comp : m_CmpInLayer[layer.first])
            {
                if (std::shared_ptr<IRenderComponent> tempP = comp.lock())
                {
                    if (tempP->getGameObject().isActive())
                    {
                        tempP->draw();
                    }
                } 
            }
        }
    }
}