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
	Tile(sf::Vector2f position, sf::Font& font, int s);
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
	void setEnd(sf::Vector2f end);
	int getCost();
	Tile* getPrevious();
	bool getStart();
	bool getGoal();
	bool getWall();
	bool getVisited();
	sf::FloatRect getRect() {return sf::FloatRect(m_rect.getPosition(), m_rect.getSize());};
	sf::Vector2f getEnd();
	sf::Vector2f getCenter();
	std::list<Tile*>& getAdj() { return adj; };
	sf::Font* m_font;
	sf::Text cost;
private:
	sf::RectangleShape m_rect;
	int size;
	std::list<Tile*> adj;
	sf::Vector2f lineEnd, center;
	Tile* m_previous;
	int m_cost;
	bool visited;
	bool start;
	bool goal;
	bool path;
	bool wall;
};