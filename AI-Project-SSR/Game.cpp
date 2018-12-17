#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Space Station Rescue", sf::Style::Default),ai_stay(Vector2f(100, 100), "Stay")
{
	m_window.setFramerateLimit(60);
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
			if (event.key.code == sf::Keyboard::Space)
			{
			}
			if (event.key.code == sf::Keyboard::Num1)
			{
			}
		}
	}
}

void Game::update(double dt)
{
	m_player.update(dt);
	ai_stay.update(dt, m_player.getPosition());
	mousePosition = sf::Mouse::getPosition(m_window);
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	ai_stay.render(m_window);
	m_player.render(m_window);
	player_camera.setCenter(sf::Vector2f(m_player.getPosition().x, m_player.getPosition().y));
	player_camera.setSize(sf::Vector2f(windowWidth, windowHeight));
	m_window.setView(player_camera);
	m_window.display();
}