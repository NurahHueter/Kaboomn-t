#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteAnimationCmp.h"
#include "RigidBodyCmp.h"
#include "VectorAlgebra2D.h"
#include "MapTile.h"
#include "Astar.h"
#include "ObjectFactory.h"
#include <random>
#include "BoxCollisionCmp.h"
#include "CowAICmp.h"
#include "PlantCmp.h"
namespace mmt_gd
{
    bool SteeringCmp::init()
    {
        int indexCorrection = 1;
        int idxw_player = static_cast<int>(gameObject.getPosition().x) / m_tileSize;
        int idxh_player = static_cast<int>(gameObject.getPosition().y) / m_tileSize;

        auto plantObject = GameObjectManager::instance().getObjectsByType(Plants);
        std::random_device rd;
        std::mt19937 gen(rd());
        if (plantObject.size() != 0)
        {
            std::uniform_int_distribution<int> distribution(0, plantObject.size() - indexCorrection);
            int m_rand = distribution(gen);
            sf::Vector2f plantPosition = plantObject[m_rand].lock()->getPosition();

            std::cout << plantPosition.x << " " << plantPosition.y << std::endl;
            std::cout << " Rand:" << m_rand << std::endl;
            std::cout << " Size:" << plantObject.size() << std::endl;
            Node start(idxh_player + indexCorrection, idxw_player + indexCorrection, 0, 0);
            int plantPositionxint = static_cast<int>(plantPosition.x) / m_tileSize;
            int plantPositionyint = static_cast<int>(plantPosition.y) / m_tileSize;
            Node goal(plantPositionyint + indexCorrection, plantPositionxint + indexCorrection, 0, 0);

            m_pathlist = AStar(MapTile::m_LayerKachel, start, goal);
        }

        return true;
    }

    void SteeringCmp::clearPath()
    {
        if (!m_pathlist.empty())
        {
            m_pathlist.clear();
        }
      
    }

    void SteeringCmp::update(float deltaTime)
    {
        if (m_astarStart)
        {
            float distanceThreshold = 0.2f;

            if (m_pathlist.empty())
            {
                handlePathCompletion();
                return;
            }

            moveTowardsNextWaypoint(deltaTime);
        }
    }

    void SteeringCmp::moveTowardsNextWaypoint(float deltaTime)
    {
        float speed = 50.0f;
        sf::Vector2f currentPosition = gameObject.getPosition();
        sf::Vector2f nextWaypoint = sf::Vector2f(m_pathlist.back().second * m_tileSize, m_pathlist.back().first * m_tileSize);

        sf::Vector2f direction = (nextWaypoint - currentPosition);
        direction /= MathUtil::length(direction);
        sf::Vector2f newPosition = currentPosition + direction * (speed * deltaTime);

        updateAnimationAndPosition(direction, newPosition, nextWaypoint);

        if (hasReachedNextWaypoint(currentPosition, nextWaypoint))
        {
            m_pathlist.pop_back();
        }
    }

    void SteeringCmp::updateAnimationAndPosition(const sf::Vector2f& direction, const sf::Vector2f& newPosition, const sf::Vector2f& nextWaypoint)
    {
        const auto& spriteAnimationCmp = gameObject.getComponent<SpriteAnimationCmp>();

        const float epsilon = 0.001;

        if (std::abs(direction.x) > epsilon || std::abs(direction.y) > epsilon) {
            // Check the larger component (x or y) to determine the dominant direction
            if (std::abs(direction.x) >= std::abs(direction.y)) {
                if (direction.x > epsilon) {
                    if (spriteAnimationCmp->getCurrentAnimation() != CowRunRight) {
                        spriteAnimationCmp->setCurrentAnimation(CowRunRight);
                    }
                }
                else if (direction.x < -epsilon) {
                    if (spriteAnimationCmp->getCurrentAnimation() != CowRunLeft) {
                        spriteAnimationCmp->setCurrentAnimation(CowRunLeft);
                    }
                }
            }
            //else {
            // 
            //    if (direction.y > epsilon) {
            //        
            //    }
            //    else if (direction.y < -epsilon) {
            //        // Set animation for moving up
            //    }
            //}
        }

        gameObject.setPosition(newPosition);
    }

    bool SteeringCmp::hasReachedNextWaypoint(const sf::Vector2f& currentPosition, const sf::Vector2f& nextWaypoint)
    {
        float distanceToNextWaypoint = MathUtil::length(nextWaypoint - currentPosition);
        return distanceToNextWaypoint < 0.2f;

    }

    void SteeringCmp::handlePathCompletion()
    {
        m_foundTarget = true;       
    }
}
