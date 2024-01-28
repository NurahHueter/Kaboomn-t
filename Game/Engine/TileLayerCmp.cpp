#pragma once
#include "pch.h"
#include "TileLayerCmp.h"
namespace mmt_gd
{
	bool TileLayerCmp::init()
	{
		return true;
	};
	void TileLayerCmp::update(float deltaTime) {};
	void TileLayerCmp::draw()
	{
		for (auto& tile : m_layer.m_tiles)
		{
				m_renderWindow.draw(*tile.m_sprite);
		}
	};		
}