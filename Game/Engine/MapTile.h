#pragma once
#include <memory>
#include <unordered_map>
#include "tileson.hpp"
#include "GameObject.h"

namespace mmt_gd
{ 
    class MapTile
    {
    public:
 
       void loadMap(const std::unique_ptr<tson::Map>& map, const fs::path m_resourcePath);

       void getTiledLayer(GameObject& gameObject, const std::unique_ptr<tson::Map>& map);

       void getObjectLayer(const std::unique_ptr<tson::Map>& map);
    };
}
