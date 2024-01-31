#pragma once
#include "pch.h"
#include "tileson.hpp"
#include "AssetManager.h"
#include "TileLayerCmp.h"
#include "MapTile.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "ObjectFactory.h"
#include <math.h>

namespace mmt_gd
{

	using namespace sf;
	using namespace std;
	std::vector<std::vector<int>> MapTile::m_LayerKachel;
	std::vector<std::vector<int>> MapTile::m_LayerKachelWithBuffer;
	sf::Vector2f MapTile::m_tileSize;

	void MapTile::loadMap(const std::unique_ptr<tson::Map>& map, const fs::path resourcePath)
	{
		
		const int numRows = 60;
		const int numCols = 60;
		//if layer 4 = 0 and layer 2 != 0

		//ground
		auto& layerData2 = map->getLayers()[1].getData();
		auto& layerData5 = map->getLayers()[5].getData();
		//collider
		auto& layerData4 = map->getLayers()[6].getData();

		m_LayerKachel.reserve(numRows);

		// Eine Reihe Polster f�r das Flugzeug - TODO

		for (int i = 0; i < numRows; ++i)
		{
			m_LayerKachel.emplace_back(); // F�gt eine leere Zeile hinzu
			m_LayerKachel[i].reserve(numCols);

			for (int j = 0; j < numCols; ++j)
			{
				// �berpr�fe, ob entweder layerData1 oder layerData2 an dieser Position nicht null ist
				if (layerData2[i * numCols + j] != 0 && layerData4[i * numCols + j] == 0 && layerData5[i * numCols + j] == 0)
				{
					m_LayerKachel[i].emplace_back(1);
				}
				else
				{
					m_LayerKachel[i].emplace_back(0);
				}
			}
		}

		m_LayerKachelWithBuffer = m_LayerKachel;

		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				// �berpr�fe, ob die Zelle im ersten Array den Wert 9 hat
				if (m_LayerKachel[i][j] == 0)
				{
					// �berpr�fe und setze die angrenzenden Zellen im zweiten Array auf 9
					for (int di = -1; di <= 1; ++di)
					{
						for (int dj = -1; dj <= 1; ++dj)
						{
							int ni = i + di;
							int nj = j + dj;

							// �berpr�fe, ob die Nachbarzellen innerhalb der Grenzen liegen
							if (ni >= 0 && ni < numRows && nj >= 0 && nj < numCols && m_LayerKachelWithBuffer[ni][nj] != 0)
							{
								m_LayerKachelWithBuffer[ni][nj] = 0;
							}
						}
					}
				}
			}
		}


		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				std::cout << m_LayerKachel[i][j] << " ";
			}
			std::cout << std::endl;
		}



		if (map->getStatus() == tson::ParseStatus::OK)
		{
			err() << "Load tile map with size: " << map->getSize().x << ", "
				<< map->getSize().y << " and tile size: " << map->getTileSize().x
				<< ", " << map->getTileSize().y << std::endl;

			for (auto& tileSet : map->getTilesets())
			{
				fs::path tileSetPath = tileSet.getImage().u8string();

				AssetManager::instance().LoadTexture(tileSet.getName(), (resourcePath / tileSetPath).string());
				if (!AssetManager::instance().m_Textures[tileSet.getName()])
				{
					err() << "Could not load texture " << resourcePath / tileSetPath << endl;
				}
			}
		}
		else
		{
			std::cout << "Parse error: " << map->getStatusMessage() << std::endl;
		}
	}

	void MapTile::getObjectLayer(const std::unique_ptr<tson::Map>& map)
	{
		for (auto group : map->getLayers())
		 {
 			// go over all objects per layer
 			for (auto object : group.getObjects())
 			{
				ObjectFactory::processTsonObject(object, group);
 			}
		 }
	}


	void MapTile::getTiledLayer(GameObject& gameObject, const std::unique_ptr<tson::Map>& map)
	{
		std::vector<TileLayer> layers;
		layers.resize(map->getLayers().size());

		for (int layerIdx = 0; layerIdx < static_cast<int>(map->getLayers().size()); layerIdx++)
		{
			auto& layer = map->getLayers()[layerIdx];

			layers[layerIdx].m_name = layer.getName();
			layers[layerIdx].m_dimension = Vector2i(layer.getSize().x, layer.getSize().y);
			layers[layerIdx].m_tileSize = Vector2i(map->getTileSize().x, map->getTileSize().y);


			const int size = layer.getSize().x * layer.getSize().y;
			// iterate over all elements/tiles in the layer
			for (int i = 0; i < size; i++)
			{
				const auto gid = layer.getData()[i];

				if (gid == 0)
				{
					// 0 means there is no tile at this position.
					continue;
				}

				// get tile set for tile and allocate the corresponding tileSet texture
				const auto* const tileSet = map->getTilesetByGid(gid);
				const Vector2i tileSize(map->getTileSize().x, map->getTileSize().y);
				const auto& texture = *AssetManager::instance().m_Textures[tileSet->getName()];
				
				// calculate position of tile
				Vector2f position;
				position.x = i % layer.getSize().x * static_cast<float>( tileSize.x);
				position.y = i / layer.getSize().x * static_cast<float>(tileSize.y);
				//position += offset;
				// number of tiles in tile set texture (horizontally)
				const int tileCountX = texture.getSize().x / tileSize.x;

				// calculate 2d idx of tile in tile set texture
				const int idx = gid - tileSet->getFirstgid();
				const int idxX = idx % tileCountX;
				const int idxY = idx / tileCountX;
				
				// calculate source area of tile in tile set texture
				IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y+1);

				//add Tile Sprite
				const auto sprite = std::make_shared<sf::Sprite>();
				sprite->setTexture(texture);
				sprite->setTextureRect(source);
				sprite->setPosition(position.x, position.y);
				layers[layerIdx].m_tiles.push_back({ i, sprite });
			}
		}
		int count = 0;
		for (auto& layer : layers)
		{
			RenderManager::instance().addLayer(layer.m_name, count);
			const auto& tileLayer = std::make_shared<TileLayerCmp>(
				gameObject,
				RenderManager::instance().getWindow(),
				layer);
			RenderManager::instance().addCompToLayer(layer.m_name, tileLayer);
			gameObject.addComponent(tileLayer);
			count++;
		}
	}
}


	