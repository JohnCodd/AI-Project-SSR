#pragma once
#include <iostream>
#include<map>
#include"SFML/Graphics.hpp"
#include "Tile.h"
class Map
{
public:
	Map(int sizeX, int sizeY, int tileSize);
	void BFS(Tile& start, Tile& goal);
	void BFS(sf::Vector2f goalPosition);
	void render(sf::RenderWindow & window);
	void rightClick(sf::Event e);
	void leftClick(sf::Event e);
	void spacebar(sf::Vector2i v);
	void onePress();
	struct VectorComparator
	{
		bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
		{
			return std::tie(lhs.x, rhs.y) < std::tie(rhs.x, lhs.y);
		}
	};
private:
	int mapWidth, mapHeight, tSize;
	std::map<sf::Vector2f, Tile, VectorComparator> tiles;
	sf::Font m_font;
	bool renderCost = true;
	Tile* startLocation;
	Tile* goalLocation;
};