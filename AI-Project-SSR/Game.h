#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include "AI.h"
#include "Map.h"
#include "Nest.h"
#include "Projectile.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	struct removeUnactiveProjectiles
	{
		bool operator()(Projectile& p) {
			return !p.getActive();
		}
	};
protected:
	void update(double dt);
	void render();
	void processEvents();
	void clampCamera();
	double windowWidth = 1400;
	double windowHeight = 800;
	double const mapWidth = 4000;
	double const mapHeight = 4000;
	float const minimapSize = 150;
	float healthWidth = 200;
	float healthHeight = 40;
	int const tileSize = 100;
	sf::RenderWindow m_window;
	sf::View player_camera, minimap;
private:
	bool updateBFS = true;
	Map m_map;
	Player m_player;
	Vector2f previousPPosition;
	sf::Vector2i mousePosition;
	std::list<Projectile> projectiles;
	std::list<AI> predators;
	std::list<Nest> nests;
};