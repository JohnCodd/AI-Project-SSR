#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "AI.h"
#include "Map.h"

class Game
{
public:
	Game();
	~Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void clampCamera();
	double windowWidth = 1400;
	double windowHeight = 800;
	double const mapWidth = 5000;
	double const mapHeight = 5000;
	int const tileSize = 50;
	sf::RenderWindow m_window;
	sf::View player_camera;
private:
	Map m_map;
	Player m_player;
	AI ai_stay;
	Vector2f previousPPosition;
	sf::Vector2i mousePosition;
};