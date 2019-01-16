#pragma once
#include "AI.h"
#include "Missile.h"
#include <list>

class Nest : public AI
{
public:
	Nest(Vector2f position, double mapX, double mapY);
	~Nest() {};
	void update(float dt, Vector2f target, Tile& targetTile);
	void render(sf::RenderWindow& window);
	struct removeUnactiveProjectiles
	{
		bool operator()(Projectile& p) {
			return !p.getActive();
		}
	};
private:
	int misileLimit = 5;
	float firingRadius = 500;
	sf::CircleShape scanArea;
	std::list<Missile> missiles;
	int shotCooldown = 0;
	int maxCooldown = 100;
};