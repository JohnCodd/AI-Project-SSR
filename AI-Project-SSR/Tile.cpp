#include "Tile.h"

Tile::Tile(sf::Vector2f position, sf::Font& font, int s)
{
	m_rect.setPosition(position);
	m_rect.setSize(sf::Vector2f(s, s));
	m_cost = 0;
	float alpha = (m_cost / 100.0f);
	m_rect.setFillColor(sf::Color(0, 0, 255, 255 - (255 * alpha)));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(2);
	m_font = &font;
	size = s;
	cost = sf::Text(std::to_string(m_cost), *m_font, 12);
	cost.setPosition(m_rect.getPosition() + sf::Vector2f(5, 5));
	center = sf::Vector2f(position.x + size / 2, position.y + size / 2);
}

void Tile::render(sf::RenderWindow * window, bool rendercost)
{
	if (start == true)
	{
		m_rect.setFillColor(sf::Color::Green);
	}
	else if (goal == true)
	{
		m_rect.setFillColor(sf::Color::Red);
	}
	else if (path == true)
	{
		m_rect.setFillColor(sf::Color::Yellow);
	}
	else if (wall == true)
	{
		m_rect.setFillColor(sf::Color::White);
	}
	else
	{
		m_rect.setFillColor(sf::Color::Transparent);
	}
	window->draw(m_rect);
	if (rendercost)
	{
		window->draw(cost);
	}
	sf::Vector2f zero = sf::Vector2f(0, 0);
	if (center != zero && lineEnd != zero)
	{
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = center;
		line[1].position = lineEnd;
		window->draw(line);
	}
}

void Tile::setCost(int ncost)
{
	m_cost = ncost;
	cost.setString(std::to_string(m_cost));
}

void Tile::setStart(bool b)
{
	start = b;
}

void Tile::setGoal(bool b)
{
	goal = b;
}

void Tile::setPath(bool b)
{
	path = b;
}

void Tile::setWall(bool b)
{
	wall = b;
}

void Tile::setPrevious(Tile &previous)
{
	m_previous = &previous;
}

void Tile::setVisited(bool b)
{
	visited = b;
}

Tile* Tile::getPrevious()
{
	return m_previous;
}

int Tile::getCost()
{
	return m_cost;
}

bool Tile::getStart()
{
	return start;
}

bool Tile::getGoal()
{
	return goal;
}

bool Tile::getWall()
{
	return wall;
}

bool Tile::getVisited()
{
	return visited;
}

sf::Vector2f Tile::getCenter()
{
	return center;
}

void Tile::addEdge(Tile& tile)
{
	adj.push_back(&tile);
}

void Tile::setEnd(sf::Vector2f end)
{
	lineEnd = end;
}

sf::Vector2f Tile::getEnd()
{
	return lineEnd;
}