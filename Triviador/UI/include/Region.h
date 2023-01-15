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
	Region(int value, int userId, int number, bool isBase);

	//setters
	void SetValue(const int& value);
	void SetCenter(const std::pair<int, int>& center);
	void SetColor(const int& color);
	void SetNumber(const int& number);
	void SetHighlight();
	void SetUserId(int userId);
	void AddNeighbour(const std::shared_ptr<Region>& region);
	void SetBase(const bool& base);

	//getters
	int GetValue() const;
	int GetNumber() const;
	std::pair <int, int> GetCenter() const;
	int GetColor() const;
	bool GetHighlight() const;
	int GetUserId() const;
	bool IsBase() const;

	bool operator<(const Region &p) const
	{
		return this->m_number < p.m_number;
	};

	void PrintRegion();

protected:
	bool m_isBase;
	int m_userId;		// negative no user
	int m_number;	
	uint16_t m_value;
	std::pair <int, int> m_center;
	std::set <std::shared_ptr<Region>> m_neighbours;
	bool m_highlight = false;
};