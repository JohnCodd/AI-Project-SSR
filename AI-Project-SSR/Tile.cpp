#include "Tile.h"

Tile::Tile(sf::Vector2f position, sf::Font& font)
{
	m_rect.setPosition(position);
	m_rect.setSize(sf::Vector2f(50, 50));
	m_cost = 0;
	float alpha = (m_cost / 100.0f);
	m_rect.setFillColor(sf::Color(0, 0, 255, 255 - (255 * alpha)));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(2);
	m_font = &font;

	cost = sf::Text(std::to_string(m_cost), *m_font, 12);
	cost.setPosition(m_rect.getPosition() + sf::Vector2f(5, 5));

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

void Tile::addEdge(Tile& tile)
{
	adj.push_back(&tile);
}