#pragma once
#include<vector>
#include<string>
#include<cstdint>
#include<set>
#include<iostream>
#include<memory>

class Region
{
public:
	Region() = default;
	Region(int value, int color, int number);

	//setters
	void SetValue(const int& value);
	void SetCenter(const std::pair<int, int>& center);
	void SetColor(const int& color);
	void SetNumber(const int& number);
	void AddNeighbour(const std::shared_ptr<Region>& region);

	//getters
	int GetValue() const;
	int GetNumber() const;
	std::pair <int, int> GetCenter() const;
	int GetColor() const;

	bool operator<(const Region &p) const
	{
		return this->m_number < p.m_number;
	};

	void PrintRegion();

protected:
	int m_number;	
	uint16_t m_value;
	std::pair <int, int> m_center;
	int m_color;
	std::set <std::shared_ptr<Region>> m_neighbours;
};