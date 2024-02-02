#pragma once
#include "GameObject.h"
#include "RenderManager.h"
#include "SpriteAnimationCmp.h"
#include "GameObjectManager.h"
#include "Tileson.hpp"

namespace tson
{
    class Object;
    class Layer;
}

namespace mmt_gd
{
    class ObjectFactory
    {
    public:
        static void processTsonObject(tson::Object& object, const tson::Layer& layer);
        static void loadPlayer(tson::Object& object, const tson::Layer& layer);
        static void loadPatch(tson::Object& object, const tson::Layer& layer);
        static void loadCow(tson::Object& object, const tson::Layer& layer);
        static std::shared_ptr<GameObject> loadPlants(const tson::Layer& layer, std::shared_ptr<GameObject> patch,int index, std::string type, std::shared_ptr<sf::Texture> texture);
        static void loadStaticCollider(tson::Object& object, const tson::Layer& layer);
        void loadStaticTrigger(tson::Object& object, const tson::Layer& layer);
        static std::vector<sf::Vector2f> m_patchPositions;
    };
} 