#pragma once
#include "GameObjectManager.h"
#include "BoxCollisionCmp.h"
#include <SFML/Graphics/Rect.hpp>

namespace mmt_gd
{
struct Manifold
{
    std::shared_ptr<BoxCollisionCmp> m_body1{};
    std::shared_ptr<BoxCollisionCmp> m_body2{};

    float    m_penetration{};
    sf::Vector2f m_normal;
};

    class RigidBodyCmp; 
    struct PhysicsManager
    {
        static
            PhysicsManager&
            instance()
        {
            static PhysicsManager s;
            return s;
        } // instance

        PhysicsManager(const PhysicsManager&) = delete;
        PhysicsManager& operator = (const PhysicsManager&) = delete;

       void addBoxCollisionCmp(std::weak_ptr<BoxCollisionCmp> component);
       std::vector<std::weak_ptr<BoxCollisionCmp>> m_bodies;
       const std::map<GameObject*, GameObject*> getCollisionPairs() { return m_collisionPairs; };

        void update();
        void shutdown();
    private:
        
        std::vector<Manifold>  m_manifolds;
        std::map<GameObject*, GameObject*> m_collisionPairs;
        void resolveCollisions(std::vector<Manifold>& m_manifolds);
        bool aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration); // returns true if interseciton
        void findCollisions(std::vector<std::weak_ptr<BoxCollisionCmp>>& m_bodies);
        PhysicsManager() {}
        ~PhysicsManager() {}
    };
}
