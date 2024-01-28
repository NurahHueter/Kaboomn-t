#pragma once
#include "IComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace mmt_gd
{
    class RigidBodyCmp; 

    class BoxCollisionCmp : public IComponent , std::enable_shared_from_this< BoxCollisionCmp >
    {
    public:
        BoxCollisionCmp(GameObject& gameObject, sf::FloatRect m_shape, bool isTrigger)
            : IComponent(gameObject), m_shape(m_shape), logicTrigger(isTrigger) {}

        bool init() override;
        void update(float deltaTime) override;


        const sf::FloatRect& getSize() const { return m_shape; }
        const sf::Vector2f& getPosition() const { return m_position; }
        bool isLogicTrigger() const { return logicTrigger; }
        std::shared_ptr<RigidBodyCmp> getRigidBody() const { return rigidBody; }


        void setLogicTrigger(bool value) { logicTrigger = value; }
        
        std::shared_ptr<RigidBodyCmp> rigidBody = nullptr;
        
        sf::FloatRect m_shape;
        sf::Vector2f m_position;
        bool logicTrigger;
    };
}
