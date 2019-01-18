#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Space Station Rescue", sf::Style::Default)
	, m_player(mapWidth, mapHeight), m_map(mapWidth, mapHeight, tileSize)
{
	previousPPosition = m_player.getPosition() / tileSize;
	m_window.setFramerateLimit(60);
	player_camera.setSize(sf::Vector2f(windowWidth, windowHeight));
	minimap.setSize(sf::Vector2f(mapWidth, mapHeight));
	minimap.setCenter(sf::Vector2f(mapWidth / 2, mapHeight / 2));
	minimap.setViewport(sf::FloatRect(0.0f, 0.0f, minimapSize / windowWidth, minimapSize / windowHeight));
	Nest nest1 = Nest(Vector2f(2000, 2000), mapWidth, mapHeight);
	Nest nest2 = Nest(Vector2f(1000, 3000), mapWidth, mapHeight);
	Nest nest3 = Nest(Vector2f(3000, 1000), mapWidth, mapHeight);
	nests.push_back(nest1);
	nests.push_back(nest2);
	nests.push_back(nest3);
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
			}
			else if (event.mouseButton.button == sf::Mouse::Left)
			{
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			//Debug testing to see BFS results from far away
			if (event.key.code == sf::Keyboard::Num0)
			{
				if (updateBFS)
				{
					updateBFS = false;
				}
				else
				{
					updateBFS = true;
				}
			}
			if (event.key.code == sf::Keyboard::Num9)
			{
				m_map.toggleDebug();
			}
		}
	}
}

void Game::clampCamera()
{
	if (player_camera.getCenter().x < windowWidth / 2)
	{
		player_camera.setCenter(windowWidth / 2, player_camera.getCenter().y);
	}
	else if (player_camera.getCenter().x > mapWidth - (windowWidth / 2))
	{
		player_camera.setCenter(mapWidth - (windowWidth / 2), player_camera.getCenter().y);
	}
	if (player_camera.getCenter().y < windowHeight / 2)
	{
		player_camera.setCenter(player_camera.getCenter().x, windowHeight / 2);
	}
	else if (player_camera.getCenter().y > mapHeight - (windowHeight / 2))
	{
		player_camera.setCenter(player_camera.getCenter().x, mapHeight - (windowHeight / 2));
	}
}

void Game::update(double dt)
{
	m_player.update(dt, m_map, projectiles);
	for (auto& p : projectiles)
	{
		p.update(dt, m_map);
		for (auto& n : nests)
		{
			if (p.getPosition().distance(n.getPosition()) < 50)
			{
				n.damage();
				p.setActive(false);
			}
		}
	}
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), removeUnactiveProjectiles()),
		projectiles.end());
	Vector2f tileLocation = Vector2f(static_cast<int>(m_player.getPosition().x / tileSize), static_cast<int>(m_player.getPosition().y / tileSize));
	if (tileLocation != previousPPosition && updateBFS)
	{
		m_map.BFS(sf::Vector2f(tileLocation.x, tileLocation.y));
	}
	previousPPosition = tileLocation;
	for (auto& n : nests)
	{
		sf::Vector2f nestLocation = sf::Vector2f(static_cast<int>(n.getPosition().x / tileSize), static_cast<int>(n.getPosition().y / tileSize));
		n.update(dt, m_player, *m_map.getTile(nestLocation), m_map, predators);
	}
	for (auto& ai : predators)
	{
		sf::Vector2f aiLocation = sf::Vector2f(static_cast<int>(ai.getPosition().x / tileSize), static_cast<int>(ai.getPosition().y / tileSize));
		ai.update(dt, m_player.getPosition(), *m_map.getTile(aiLocation));
	}
	mousePosition = sf::Mouse::getPosition(m_window);
	if (m_player.getPosition().x < 200 && m_player.getPosition().y < 200)
	{
		minimap.setViewport(sf::FloatRect(1.0f - minimapSize / windowWidth, 0.0f, minimapSize / windowWidth, minimapSize / windowHeight));
	}
	else
	{
		minimap.setViewport(sf::FloatRect(0.0f, 0.0f, minimapSize / windowWidth, minimapSize / windowHeight));
	}
}

void Game::render()
{
	//Display the game boundries
	sf::RectangleShape border = sf::RectangleShape(sf::Vector2f(mapWidth, mapHeight));
	border.setPosition(0, 0);
	border.setOutlineColor(sf::Color::Red);
	border.setOutlineThickness(5);
	border.setFillColor(sf::Color::Transparent);
	m_window.clear(sf::Color(0, 0, 0, 0));
	player_camera.setCenter(sf::Vector2f(m_player.getPosition().x, m_player.getPosition().y));
	clampCamera();
	m_window.setView(player_camera);
	m_map.render(m_window);
	//m_window.setView(m_window.getDefaultView());
	for (auto& ai : predators)
	{
		ai.render(m_window);
	}
	for (auto& n : nests)
	{
		n.render(m_window);
	}
	m_player.render(m_window);
	for (auto& p : projectiles)
	{
		p.render(m_window);
	}
	m_window.draw(border);
	m_window.setView(minimap);
	sf::CircleShape playerIcon;
	sf::RectangleShape background;
	//Show player and nest positions on the map
	float radius = 100;
	playerIcon.setRadius(radius);
	playerIcon.setFillColor(sf::Color::Blue);
	playerIcon.setPosition(sf::Vector2f(m_player.getPosition().x - radius, m_player.getPosition().y - radius));
	background.setSize(sf::Vector2f(mapWidth, mapHeight));
	background.setFillColor(sf::Color::Green);
	background.setPosition(sf::Vector2f(0, 0));
	m_window.draw(background);
	m_window.draw(playerIcon);
	for (auto& n : nests)
	{
		if (n.getActive())
		{
			sf::CircleShape nestIcon;
			nestIcon.setRadius(radius);
			nestIcon.setFillColor(sf::Color::Red);
			nestIcon.setPosition(sf::Vector2f(n.getPosition().x - radius, n.getPosition().y - radius));
			m_window.draw(nestIcon);
		}
	}
	m_window.setView(player_camera);
	// Draw the health bar
	sf::RectangleShape healthOuter = sf::RectangleShape(sf::Vector2f(healthWidth, healthHeight));
	healthOuter.setPosition(player_camera.getCenter().x - ((windowWidth / 2) - 5), player_camera.getCenter().y + ((windowHeight / 2) - (healthHeight + 5)));
	healthOuter.setOutlineColor(sf::Color::Red);
	healthOuter.setOutlineThickness(5);
	healthOuter.setFillColor(sf::Color::Transparent);
	sf::RectangleShape healthInner = sf::RectangleShape(sf::Vector2f(healthWidth * ((float)m_player.getHealth() / (float)m_player.getMaxHealth()), healthHeight));
	healthInner.setPosition(player_camera.getCenter().x - ((windowWidth / 2) - 5), player_camera.getCenter().y + ((windowHeight / 2) - (healthHeight + 5)));
	healthInner.setFillColor(sf::Color::Green);
	m_window.draw(healthInner);
	m_window.draw(healthOuter);
	m_window.display();
}