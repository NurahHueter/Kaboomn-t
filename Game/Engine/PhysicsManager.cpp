#pragma once

#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "PhysicsManager.h"
#include "RigidBodyCmp.h"
#include "ObjectTypes.h"
#include "GameObjectManager.h"
namespace mmt_gd
{
     void PhysicsManager::addBoxCollisionCmp(std::weak_ptr<BoxCollisionCmp> component)
     {
             m_bodies.push_back(component);
     }

    bool PhysicsManager::aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration)
    {
        auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
            { return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height); };


        sf::Vector2f n = getCenter(b) - getCenter(a); // Vector from A to B
        float    a_extent = a.width * 0.5f;              // Calculate half extents along x axis
        float    b_extent = b.width * 0.5f;
        float    x_overlap = a_extent + b_extent - abs(n.x); // Calculate overlap on x axis
        // SAT test on x axis
        if (x_overlap > 0)
        {
            float a_extent = a.height * 0.5f; // Calculate half extents along y axis
            float b_extent = b.height * 0.5f;
            float y_overlap = a_extent + b_extent - abs(n.y); // Calculate overlap on y axis

            // SAT test on y axis
            if (y_overlap > 0)
            {
                // Find out which axis is axis of least penetration
                if (x_overlap < y_overlap)
                {
                    // Point towards B knowing that n points from A to B
                    if (n.x < 0)
                        normal = sf::Vector2f(1.0f, 0.0f);
                    else
                        normal = sf::Vector2f(-1.0f, 0.0f);
                    penetration = x_overlap;
                    return true;
                }
                else
                {
                    // Point towards B knowing that n points from A to B
                    if (n.y < 0)
                        normal = sf::Vector2f(0, 1);
                    else
                        normal = sf::Vector2f(0, -1);
                    penetration = y_overlap;
                    return true;
                }
            }
        }
        return false;
    }

    void PhysicsManager::update()
    {   
        m_collisionPairs.clear();
        m_manifolds.clear();
        findCollisions(m_bodies);
        resolveCollisions(m_manifolds);

    }
 
    void PhysicsManager::findCollisions(std::vector<std::weak_ptr<BoxCollisionCmp>>& m_bodies)
    {
        //checks if all ptr have a reverence and makes temp shared ptr
        std::vector<std::shared_ptr<BoxCollisionCmp>> bodies;
        for (auto body : m_bodies)
        {
            if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
            {
                if(tempP->getGameObject().isActive())
                bodies.push_back(tempP);
            }
        }

        for (auto itA = bodies.begin(); itA != bodies.end(); ++itA)
        {
           
            auto& body1 = *itA;
            for (auto itB = itA; itB != bodies.end(); ++itB)
            {
               
                if (itB == itA)
                    continue;
           
                auto& body2 = *itB;
                // if both object don't have a mass or body is the same skip
                if (!body1->rigidBody && !body2->rigidBody)
                    continue;

               
                sf::Transform body1Transform;
                body1Transform.translate(body1->m_position);
                sf::Transform body2Transform;
                body2Transform.translate(body2->m_position);

                sf::Vector2f normal;
                float    penetration = NAN;
                if (aabbVsAabb(body1Transform.transformRect(body1->m_shape),
                    body2Transform.transformRect(body2->m_shape),
                    normal,
                    penetration))
                {
                    Manifold manifold;
                    manifold.m_body1 = body1;
                    manifold.m_body2 = body2;
                    manifold.m_normal = normal;
                    manifold.m_penetration = penetration;

                    m_manifolds.push_back(manifold);
                }
            }
        }
    }

    void PhysicsManager::resolveCollisions( std::vector<Manifold>& m_manifolds)
    {
        for (auto man : m_manifolds)
        {
            if (&man.m_body1->getGameObject() == &man.m_body2->getGameObject())
            {
                continue;
            }

            if (man.m_body1->isLogicTrigger() || man.m_body2->isLogicTrigger())
            {
                
                if (man.m_body1->isLogicTrigger())
                {
                    m_collisionPairs.insert(std::make_pair(&man.m_body1->getGameObject(), &man.m_body2->getGameObject()));
                }
                if (man.m_body2->isLogicTrigger())
                {
                    m_collisionPairs.insert(std::make_pair(&man.m_body2->getGameObject(), &man.m_body1->getGameObject()));
                }
            }
            else
            {
           
                sf::Vector2f rv = man.m_body1->rigidBody->getVelocity() - man.m_body2->rigidBody->getVelocity();
                // Calculate relative velocity in terms of the normal direction

            }
        }
    }

    void PhysicsManager::shutdown()
    {
        m_manifolds.clear();
        m_bodies.clear();
    }

}