#pragma once
#include"Region.h"

class Tile
{
public:
	Tile();
	void SetTile(const std::pair<int, int>& coordinates,const std::shared_ptr<Region>& region);
	void SetBorder();
	bool IsBorder();
	std::pair<int, int> GetCoordinate() const;
	std::shared_ptr<Region> getParentRegion();

protected:
	bool m_isBorder;
	std::pair<int, int> m_coordinates;
	std::shared_ptr<Region> m_region;
};

