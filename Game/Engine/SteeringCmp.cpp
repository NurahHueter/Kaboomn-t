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

namespace mmt_gd
{
    bool SteeringCmp::init() 
    {
        // Position from the ai on the grid
        int idxw_player = (gameObject.getPosition().x + (m_sizeX / 2)) / MapTile::m_tileSize.x;    
        int idxh_player = (gameObject.getPosition().y + (m_sizeY / 2)) / MapTile::m_tileSize.x;

        m_target = GameObjectManager::instance().getGameObject("Player")->getPosition();
        // Create start and goal nodes
        Node start(idxh_player, idxw_player, 0, 0); 
        Node goal((m_target.y  / MapTile::m_tileSize.x), (m_target.x / MapTile::m_tileSize.y),0,0); 
        
        // Call A* algorithm
        m_pathlist = AStar(MapTile::m_LayerKachelWithBuffer, start, goal);

        return true;
    };
    void SteeringCmp::update(float deltaTime)
    {
        constexpr float acc = 300.0f; 
        sf::Vector2f accVec;

        static sf::Clock movementClock; 
		static sf::Clock movementClock2;


        if (movementClock2.getElapsedTime().asSeconds() >= 2.f)
        {	
			int idxw_player = (gameObject.getPosition().x + (m_sizeX / 2)) / MapTile::m_tileSize.x;         
			int idxh_player = (gameObject.getPosition().y + (m_sizeY / 2)) / MapTile::m_tileSize.y;

			// Create start and goal nodes
			Node start(idxh_player, idxw_player, 0, 0); 
			Node goal((m_target.y / MapTile::m_tileSize.x), (m_target.x / MapTile::m_tileSize.y), 0, 0);
            m_pathlist.clear();

			// Call A* algorithm
			m_pathlist = AStar(MapTile::m_LayerKachelWithBuffer, start, goal);

            //std::cout << gameObject.getId() << m_target.x;
			movementClock2.restart();
        }

        if (movementClock.getElapsedTime().asSeconds() >= 0.1f)
        {
            if (!m_pathlist.empty())
            {
                auto path = m_pathlist.rbegin(); // Get the next path

                nextTarget = sf::Vector2f(path->second * 16, path->first * 16);

                m_pathlist.pop_back(); // Remove the used path from the list

                movementClock.restart(); // Restart the clock for the next second
            }
        }

        sf::Vector2f direction = nextTarget - gameObject.getPosition();
        const auto animation = gameObject.getComponent<SpriteAnimationCmp>();
        sf::Vector2f distance = MathUtil::unitVector(direction);

        if (std::abs(distance.x) > std::abs(distance.y))
        {
            // horizontal movement
            accVec = { (distance.x > 0) ? acc : -acc, 0.0f };
            animation->setCurrentAnimation((distance.x > 0) ? MoveRight : MoveLeft);
        }
        else
        {
            // vertical movement
            accVec = { 0.0f, (distance.y > 0) ? acc : -acc };
            animation->setCurrentAnimation((distance.y > 0) ? MoveDown : MoveUp);
        }

        if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
        {
            rigidBodyCmp->setVelocityP(accVec * deltaTime);
            rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity() - (rigidBodyCmp->getVelocity() * 0.99f));
            rigidBodyCmp->setImpulse(accVec);
            rigidBodyCmp->setPosition(rigidBodyCmp->getVelocity(), deltaTime);
            gameObject.setPosition(rigidBodyCmp->getPosition());
        }
    }
}