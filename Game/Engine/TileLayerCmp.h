#pragma once
#include "IRenderComponent.h"
#include<memory>

namespace mmt_gd
{
	struct Tile
	{
		/**
		 * \brief original tile index
		 */
		int                         m_idx;
		std::shared_ptr<sf::Sprite> m_sprite;
	};
	struct TileLayer
	{
		std::string       m_name;
		sf::Vector2i      m_dimension;
		sf::Vector2i      m_tileSize;
		std::vector<Tile> m_tiles;
	};
	class TileLayerCmp : public IRenderComponent
	{
	public:
		TileLayerCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, TileLayer& layer)
			: IRenderComponent(gameObject, renderWindow), m_layer(layer)
		{};
		~TileLayerCmp() {};
		bool init() override;
		void update(float deltaTime) override;
		void draw() override;
	private:
		TileLayer m_layer;
	};
}

