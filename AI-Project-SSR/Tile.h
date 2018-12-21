#pragma once
#include "SFML/Graphics.hpp"
#include <list>

struct VectorComparator
{
	bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
	{
		return std::tie(lhs.x, rhs.y) < std::tie(rhs.x, lhs.y);
	}
};

class Tile
{
public:
	Tile() {};
	Tile(sf::Vector2f position, sf::Font& font);
	~Tile() {};
	void render(sf::RenderWindow * window, bool rendercost);
	void setCost(int cost);
	void setPrevious(Tile &previous);
	void setGoal(bool b);
	void setStart(bool b);
	void setPath(bool b);
	void setWall(bool b);
	void setVisited(bool b);
	void addEdge(Tile& tile);
	int getCost();
	Tile* getPrevious();
	bool getStart();
	bool getGoal();
	bool getWall();
	bool getVisited();
	std::list<Tile*>& getAdj() { return adj; };
	sf::Font* m_font;
	sf::Text cost;
private:
	sf::RectangleShape m_rect;
	std::list<Tile*> adj;
	Tile* m_previous;
	int m_cost;
	bool visited;
	bool start;
	bool goal;
	bool path;
	bool wall;
};