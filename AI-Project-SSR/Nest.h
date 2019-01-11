#pragma once
#include "AI.h"

class Nest : public AI
{
public:
	Nest(Vector2f position, double mapX, double mapY);
	~Nest() {};
	void update(float dt, Vector2f target, Tile& targetTile);
	void render(sf::RenderWindow& window);
private:
	int misileLimit = 5;
	float firingRadius = 500;
	sf::CircleShape scanArea;
};