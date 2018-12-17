#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "AI.h"

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
	double windowWidth = 1400;
	double windowHeight = 800;
	sf::RenderWindow m_window;
	sf::View player_camera;
private:
	Player m_player;
	AI ai_stay;
	sf::Vector2i mousePosition;
};