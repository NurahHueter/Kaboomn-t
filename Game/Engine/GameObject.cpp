/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah H�ter, Florian Rauter
*/
#include "pch.h"
#include "GameObject.h"
#include "IRenderComponent.h"

namespace mmt_gd
{
    void GameObject::addComponent(const IComponent::Ptr& component)
    {
        m_componentList.push_back(component);
    }

    void GameObject::removeComponent(const IComponent::Ptr& component)
    {
        if (const auto it = std::find(m_componentList.begin(), m_componentList.end(), component); it != m_componentList.end())
        {
            m_componentList.erase(it);
        }
    }

    void GameObject::update(const float deltaTime) const
    {
        for (const auto& comp : m_componentList)
        {
            comp->update(deltaTime);
        }
    }

    void GameObject::draw() const
    {
        for (const auto& component : m_componentList)
        {
            if (const auto comp = std::dynamic_pointer_cast<IRenderComponent>(component))
            {
                comp->draw();
            }
        }
    }

    bool GameObject::init() const
    {
        for (const auto& comp : m_componentList)
        {
            if (!comp->init())
            {
                sf::err() << "Could not initialize component of object " << m_id << std::endl;
                return false;
            }
            else
            {
                comp->init();
            }
        }
        return true;
    }
    void GameObject::setMiddle(sf::Vector2f middle)
    {
       m_middle = middle - getPosition();
    };
    void GameObject::setDrawPoint(sf::Vector2f drawPoint)
    { 
        m_drawPoint = drawPoint - getPosition();
    }; 
    sf::Vector2f GameObject::getMiddle()
    {
        return getPosition() + m_middle;
    };
    sf::Vector2f GameObject::getDrawPoint()
    {
        return getPosition() + m_drawPoint;
    };
}
     
