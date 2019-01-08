#include "Map.h"

Map::Map(int sizeX, int sizeY, int tileSize)
{
	mapWidth = sizeX / tileSize;
	mapHeight = sizeY / tileSize;
	tSize = tileSize;
	if (!m_font.loadFromFile("./times.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			Tile t = Tile(sf::Vector2f(j * tSize, i * tSize), m_font, tileSize);
			sf::Vector2f location = sf::Vector2f(j, i);
			sf::Vector2f newLocation;
			tiles[location] = t;
			int current = (j + (i * mapWidth));
			if (i > 0)
			{
				newLocation = sf::Vector2f(j, i - 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (j + 1 < mapWidth)
			{
				newLocation = sf::Vector2f(j + 1, i);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (i + 1 < mapHeight)
			{
				newLocation = sf::Vector2f(j, i + 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (i > 0 && j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i - 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (i + 1 < mapHeight && j + 1 < mapWidth)
			{
				newLocation = sf::Vector2f(j + 1, i + 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (i + 1 < mapHeight && j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i + 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (j + 1 < mapWidth && i > 0)
			{
				newLocation = sf::Vector2f(j + 1, i - 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
		}
	}
	tiles[sf::Vector2f(10, 10)].setWall(true);
	tiles[sf::Vector2f(10, 11)].setWall(true);
	tiles[sf::Vector2f(10, 12)].setWall(true);
	tiles[sf::Vector2f(10, 13)].setWall(true);
	tiles[sf::Vector2f(10, 14)].setWall(true);
	tiles[sf::Vector2f(11, 14)].setWall(true);
	tiles[sf::Vector2f(12, 14)].setWall(true);
	tiles[sf::Vector2f(13, 14)].setWall(true);
	tiles[sf::Vector2f(14, 14)].setWall(true);
	//startLocation = &tiles[sf::Vector2f(18, 5)];
	//goalLocation = &tiles[sf::Vector2f(6, 42)];
	//BFS(*startLocation, *goalLocation);
	//std::cout << "Left click: Set the start position (Green)" << std::endl;
	//std::cout << "Right click: Set the goal position (Red)" << std::endl;
	//std::cout << "Spacebar: Toggle a wall (White)" << std::endl;
	//std::cout << "1: Toggle the tile costs" << std::endl;
}


void Map::BFS(Tile& start, Tile& goal)
{

	// Mark all the vertices as not visited 
	bool goalReached = false;

	// Create a queue for BFS 
	std::list<Tile*> queue;
	for (auto &tile : tiles)
	{
		tile.second.setStart(false);
		tile.second.setGoal(false);
		tile.second.setPath(false);
		tile.second.setVisited(false);
		tile.second.setCost(0);
	}
	// Mark the current node as visited and enqueue it 
	startLocation = &start;
	goalLocation = &goal;
	start.setStart(true);
	start.setVisited(true);
	goal.setGoal(true);
	queue.push_back(&start);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 

	int cost = 1;
	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		int originCost = queue.front()->getCost();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (auto &e : queue.front()->getAdj())
		{
			if (e == &goal)
			{
				goalReached = true;
			}
			if (e->getVisited() == false)
			{
				e->setVisited(true);
				if (e->getWall() == false)
				{
					e->setCost(originCost + 1);
					e->setPrevious(*queue.front());
					queue.push_back(e);
				}
			}
		}
		queue.pop_front();
	}
	if (goalReached == true)
	{
		std::vector<Tile*> outputVec;
		Tile* previous = &goal;
		int x, y;
		sf::Vector2f tileLocation;
		bool isStart = false;
		while (isStart != true)
		{
			outputVec.push_back(previous);
			previous = previous->getPrevious();
			isStart = previous->getStart();
		}
		for (auto &e : outputVec)
		{
			e->setPath(true);
		}
	}
}

void Map::BFS(sf::Vector2f goalPosition)
{

	Tile* goal = &tiles[goalPosition];

	// Mark all the vertices as not visited 
	bool goalReached = false;

	// Create a queue for BFS 
	std::list<Tile*> queue;
	for (auto &tile : tiles)
	{
		tile.second.setStart(false);
		tile.second.setGoal(false);
		tile.second.setPath(false);
		tile.second.setVisited(false);
		tile.second.setCost(0);
	}
	// Mark the current node as visited and enqueue it 
	//startLocation = &start;
	//goalLocation = &goal;
	//start.setStart(true);
	//start.setVisited(true);
	goal->setGoal(true);
	goal->setVisited(true);
	queue.push_back(goal);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 

	int cost = 1;
	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		int originCost = queue.front()->getCost();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (auto &e : queue.front()->getAdj())
		{
			//if (e == &goal)
			//{
			//	goalReached = true;
			//}
			if (e->getVisited() == false)
			{
				e->setVisited(true);
				if (e->getWall() == false)
				{
					e->setCost(originCost + 1);
					e->setPrevious(*queue.front());
					queue.push_back(e);
				}
			}
		}
		queue.pop_front();
	}
	for (auto &t : tiles)
	{
		if (t.second.getPrevious() && t.second.getWall() == false)
		{
			t.second.setEnd(t.second.getPrevious()->getCenter());
		}
	}
	//if (goalReached == true)
	//{
	//	std::vector<Tile*> outputVec;
	//	Tile* previous = &goal;
	//	int x, y;
	//	sf::Vector2f tileLocation;
	//	bool isStart = false;
	//	while (isStart != true)
	//	{
	//		outputVec.push_back(previous);
	//		previous = previous->getPrevious();
	//		isStart = previous->getStart();
	//	}
	//	for (auto &e : outputVec)
	//	{
	//		e->setPath(true);
	//	}
	//}
}

void Map::render(sf::RenderWindow & window)
{
	for (auto const& a : tiles)
	{
		tiles[a.first].render(&window, renderCost);
	}
}

void Map::rightClick(sf::Event e)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(e.mouseButton.x / tSize), ceil(e.mouseButton.y / tSize));
	sf::Vector2f tileLocation = sf::Vector2f((mousePosition.x), (mousePosition.y));
	BFS(*startLocation, tiles[tileLocation]);
}

void Map::leftClick(sf::Event e)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(e.mouseButton.x / tSize), ceil(e.mouseButton.y / tSize));
	sf::Vector2f tileLocation = sf::Vector2f((mousePosition.x), (mousePosition.y));
	BFS(tiles[tileLocation], *goalLocation);
}

void Map::spacebar(sf::Vector2i v)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(v.x / tSize), ceil(v.y / tSize));
	sf::Vector2f tileLocation = sf::Vector2f((mousePosition.x), (mousePosition.y));
	if (tiles[tileLocation].getWall() == true)
	{
		tiles[tileLocation].setWall(false);
	}
	else
	{
		tiles[tileLocation].setWall(true);
	}
}

void Map::onePress()
{
	if (renderCost == true)
	{
		renderCost = false;
	}
	else
	{
		renderCost = true;
	}
}

bool Map::checkCollision(sf::FloatRect r)
{
	for (auto& t : tiles)
	{
		if (t.second.getWall())
		{
			sf::FloatRect rect = t.second.getRect();
			if (rect.intersects(r))
			{
				return true;
			}
		}
	}
	return false;
}

Tile* Map::getTile(sf::Vector2f v)
{
	return &tiles[v];
}
