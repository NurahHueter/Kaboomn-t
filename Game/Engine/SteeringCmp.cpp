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
namespace mmt_gd
{
    bool SteeringCmp::init() 
    {
        ;
        //// Position from the ai on the grid
        int idxw_player = (gameObject.getPosition().x ) / 16;    
        int idxh_player = (gameObject.getPosition().y) / 16;
   
        // Create start and goal nodes

        auto plantObject = GameObjectManager::instance().getObjectsByType(Plants);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, plantObject.size() - 1);
        int rand = distribution(gen);

        //srand(time(0));
   
        ////random plants posiiton
        //int rand = std::rand() % plantObject.size();

        sf::Vector2f plantPosition = plantObject[rand].lock()->getPosition();
       
      
        Node start(idxh_player+1, idxw_player+1, 0, 0);
        int plantPositionxint = static_cast<int>(plantPosition.x)/16;
        int plantPositionyint = static_cast<int>(plantPosition.y)/16;
        std::cout << plantPositionxint << " pos " << plantPositionyint << std::endl;
        Node goal(plantPositionyint+1, plantPositionxint+1, 0, 0);
        //y,x
        //Node goal((46), (15), 0, 0);
        // Call A* algorithm
       m_pathlist = AStar(MapTile::m_LayerKachel, start, goal);

       std::cout << idxh_player << " Width: " << idxw_player << std::endl;

     
        return true;
     
    };
    void SteeringCmp::update(float deltaTime)
    {


  //      constexpr float acc = 300.0f; 
  //      sf::Vector2f accVec;

        //
		//static sf::Clock movementClock2;

     
  //      if (movementClock2.getElapsedTime().asSeconds() >= 2.f)
  //      {	
		//	int idxw_player = (gameObject.getPosition().x + (m_sizeX / 2)) / MapTile::m_tileSize.x;         
		//	int idxh_player = (gameObject.getPosition().y + (m_sizeY / 2)) / MapTile::m_tileSize.y;

		//	// Create start and goal nodes
		//	Node start(idxh_player, idxw_player, 0, 0); 
		//	Node goal((m_target.y / MapTile::m_tileSize.x), (m_target.x / MapTile::m_tileSize.y), 0, 0);
  //          m_pathlist.clear();

		//	// Call A* algorithm
		//	m_pathlist = AStar(MapTile::m_LayerKachelWithBuffer, start, goal);

  //          //std::cout << gameObject.getId() << m_target.x;
		//	movementClock2.restart();
  //      }


        static sf::Clock movementClock;


        if (movementClock.getElapsedTime().asSeconds() >= .2f)
        {
            if (!m_pathlist.empty())
            {
                auto path = m_pathlist.rbegin(); // Get the next path
                //std::cout << path.x << " " << path.y << std::endl;
                nextTarget   = sf::Vector2f(path->second * 16, path->first * 16);

                std::cout << path->second << " Target "<< path->first << std::endl;
                m_pathlist.pop_back(); // Remove the used path from the list

                movementClock.restart(); // Restart the clock for the next second
            }
            //cursed
           // gameObject.setPosition(nextTarget.x-16, nextTarget.y - 16);

            if (nextTarget.x >= gameObject.getPosition().x)
            {
                gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowRunRight);
            }
            if (nextTarget.x < gameObject.getPosition().x)
            {
                gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowRunLeft);
            }
            gameObject.setPosition(nextTarget.x, nextTarget.y);

            if (m_pathlist.empty())
            {
                gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleChewLeft);
            }

       
        }
  


        
            // horizontal movement
     
            
        
        //else
        //{
        //    // vertical movement
        //    accVec = { 0.0f, (distance.y > 0) ? acc : -acc };
        //    animation->setCurrentAnimation((distance.y > 0) ? MoveDown : MoveUp);
        //}

        //if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
        //{
        //    rigidBodyCmp->setVelocityP(accVec * deltaTime);
        //    rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity() - (rigidBodyCmp->getVelocity() * 0.99f));
        //    rigidBodyCmp->setImpulse(accVec);
        //    rigidBodyCmp->setPosition(rigidBodyCmp->getVelocity(), deltaTime);
        //    gameObject.setPosition(rigidBodyCmp->getPosition());
        //}
    }
}