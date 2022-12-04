#pragma once
#include<vector>
#include<string>

namespace DB
{
	class Region
	{
	public:
		Region() = default;
		Region(std::vector<std::pair<int, int>> tiles, int value, std::pair <int, int> center, std::string color, std::vector<Region*> neighbours);

		//setters
		void SetTitles(std::vector<std::pair<int, int>> tiles);
		void SetValue(int value);
		void SetCenter(std::pair<int, int> center);
		void SetColor(std::string color);
		void SetNeighbours(std::vector<Region*> neighbours);

		//getters
		std::vector<std::pair<int, int>> GetTiles() const;
		int GetValue() const;
		std::pair <int, int> GetCenter() const;
		std::string GetColor() const;
		std::vector<Region*> GetNeighbours() const;

	protected:
		std::vector<std::pair<int, int>> m_tiles;
		int m_value;
		std::pair <int, int> m_center;
		std::string m_color;
		std::vector<Region*> m_neighbours;
	};
}