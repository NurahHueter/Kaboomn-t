#include "pch.h"
#include "CowAICmp.h"
#include "AnimationTypes.h"
#include "SpriteAnimationCmp.h"
#include "GameObject.h"
#include "InputManager.h"


namespace mmt_gd
{

    bool CowAICmp::init()
    {
        gameObject.getComponent<SpriteAnimationCmp>()->setCurrentAnimation(CowIdleEatLeft);
        return true;
    }

    void CowAICmp::update(float deltaTime)
    {

        //    const auto player = GameObjectManager::instance().getGameObject("Player");
        //    const auto texture = player->getComponent<SpriteAnimationCmp>()->getTextureRect().getSize();
        //    playerPosition = sf::Vector2f(player->getPosition().x + texture.x / 2, player->getPosition().y + texture.y / 2);


        //    distance_x = std::abs(playerPosition.x - gameObject.getPosition().x);
        //    distance_y = std::abs(playerPosition.y - gameObject.getPosition().y);

        //    if (distance_x < m_attackRange || distance_y < m_attackRange)
        //    {
        //        currentState = Attack;
        //    }
        //    if (distance_x > m_attackRange || distance_y > m_attackRange)
        //    {
        //        currentState = Patrol;
        //    }
        //    //if (gameObject.getComponent<HealthCmp>()->getHealth() == 1
        //    //    && (distance_x < m_attackRange || distance_y < m_attackRange))
        //    //{
        //    //    currentState = Flee;
        //    //};

        //    switch (currentState)
        //    {
        //    case Patrol:
        //        patrol();
        //        break;
        //    case Attack:
        //        attack();
        //        break;
        //        //case Flee:
        //        //    flee();
        //        //    break;
        //    default:
        //        break;
        //    }
        //};


        //void CowAICmp::patrol()
        //{

        //    if (m_patrolPoints.size() > 1)
        //    {
        //        gameObject.getComponent<SteeringCmp>()->setTarget(m_patrolPoints[m_currentWayPoint]);
        //        float distanceToTarget = MathUtil::length(m_patrolPoints[m_currentWayPoint] - gameObject.getPosition());
        //        float patrolRadius = 20.0f;
        //        if (distanceToTarget <= patrolRadius)
        //        {
        //            m_currentWayPoint++;
        //            if (m_currentWayPoint >= m_patrolPoints.size())
        //            {
        //                m_currentWayPoint = 0;
        //            }
        //        }
        //    }
        //};
        //void CowAICmp::attack()
        //{
        //    gameObject.getComponent<SteeringCmp>()->setTarget(playerPosition);
        //    gameObject.getComponent<ProjectileCmp>()->shoot(playerPosition);

        //};
        ////void AIControllerCmp::flee()
        ////{
        ////    auto playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        ////    sf::Vector2f fleePoint = sf::Vector2f(playerPosition.x * -1, playerPosition.y * -1);

        ////    gameObject.getComponent<SteeringCmp>()->setTarget(fleePoint);
        ////};
    }
}