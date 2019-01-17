#pragma once
#include "AI.h"
#include "Player.h"
#include "Missile.h"
#include "Map.h"
#include <list>

class Nest : public AI
{
public:
	Nest(Vector2f position, double mapX, double mapY);
	~Nest() {};
	void update(float dt, Player& player, Tile& targetTile, Map& m);
	void render(sf::RenderWindow& window);
	void damage();
	bool getActive() { return active; }
	struct removeUnactiveProjectiles
	{
		bool operator()(Projectile& p) {
			return !p.getActive();
		}
	};
private:
	int misileLimit = 1;
	float firingRadius = 500;
	sf::CircleShape scanArea;
	std::list<Missile> missiles;
	int shotCooldown = 0;
	int maxCooldown = 100;
	int health;
	int maxHealth = 4;
	bool active = true;
};