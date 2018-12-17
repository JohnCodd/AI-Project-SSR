#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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
private:
	sf::Vector2i mousePosition;
};