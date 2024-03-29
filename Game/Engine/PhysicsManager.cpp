/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah H�ter, Florian Rauter
*/
#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "PhysicsManager.h"
#include "BoxCollisionCmp.h"
#include "ObjectTypes.h"
#include "GameObjectManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"

namespace mmt_gd
{
    void PhysicsManager::addBoxCollisionCmp(std::weak_ptr<BoxCollisionCmp> component)
    {
        m_bodies.push_back(component);
    }

    void PhysicsManager::update()
    { 
        m_collisionPairs.clear();
        findCollisions(m_bodies);
    }

    void PhysicsManager::findCollisions(std::vector<std::weak_ptr<BoxCollisionCmp>>& m_bodies)
    {
        std::vector<std::shared_ptr<BoxCollisionCmp>> bodies;
        for (auto body : m_bodies)
        {
            if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
            {
                if (tempP->getGameObject().isActive())
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

                sf::Transform body1Transform;
                body1Transform.translate(body1->m_position);
                sf::Transform body2Transform;
                body2Transform.translate(body2->m_position);

                sf::Vector2f normal;
                float penetration = NAN;
                if (aabbVsAabb(body1Transform.transformRect(body1->m_shape),
                    body2Transform.transformRect(body2->m_shape),
                    normal,
                    penetration))
                {
                    if (body1->isLogicTrigger() || body2->isLogicTrigger())
                    {
                        if (body1->isLogicTrigger())
                        {
                            m_collisionPairs.insert(std::make_pair(&body1->getGameObject(), &body2->getGameObject()));
                        }
                        if (body2->isLogicTrigger())
                        {
                            m_collisionPairs.insert(std::make_pair(&body2->getGameObject(), &body1->getGameObject()));
                        }

                    }
                    else
                    {
                        sf::Vector2f separationVector = normal * penetration;

                        if (body1->getGameObject().getComponent<MoveCmp>())
                        {
                            body1->getGameObject().setPosition(body1->getGameObject().getPosition() + separationVector);
                        }
                        else
                        {
                            body2->getGameObject().setPosition(body2->getGameObject().getPosition() + separationVector);
                        }
                    }
                }
            }
        }
    }


    void PhysicsManager::shutdown()
    {
        m_bodies.clear();
    }

    bool PhysicsManager::aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration)
    {
        auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
            {
                return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
            };

        sf::Vector2f n = getCenter(b) - getCenter(a); // Vector from A to B
        float a_extent = a.width * 0.5f; // Calculate half extents along x axis
        float b_extent = b.width * 0.5f;
        float x_overlap = a_extent + b_extent - std::abs(n.x); // Calculate overlap on x axis

        // SAT test on x axis
        if (x_overlap > 0)
        {
            float a_extent = a.height * 0.5f; // Calculate half extents along y axis
            float b_extent = b.height * 0.5f;
            float y_overlap = a_extent + b_extent - std::abs(n.y); // Calculate overlap on y axis

            // SAT test on y axis
            if (y_overlap > 0)
            {
                // Find out which axis is the axis of least penetration
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

}
