#include "Tile.h"

Tile::Tile()
{
	m_isBorder = 0;
	m_coordinates.first = -1;
	m_coordinates.second = -1;
	m_region = nullptr;
}

void Tile::SetTile(const std::pair<int, int>& coordinates,const std::shared_ptr<Region>& region)
{
	m_coordinates = coordinates;
	m_region = region;
}

void Tile::SetBorder()
{
	m_isBorder = 1;
}

bool Tile::IsBorder()
{
	return m_isBorder;
}

std::pair<int, int> Tile::GetCoordinate() const
{
	return m_coordinates;
}

std::shared_ptr<Region> Tile::getParentRegion()
{
	return m_region;
}
