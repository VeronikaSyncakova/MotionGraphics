#include "Game.h"
#include <iostream>

// Our target FPS
static double const FPS{ 60.0f };

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
{
	init();

}

////////////////////////////////////////////////////////////
void Game::init()
{
	// Really only necessary is our target FPS is greater than 60.
	m_window.setVerticalSyncEnabled(true);

	if (!m_arialFont.loadFromFile("BebasNeue.otf"))
	{
		std::cout << "Error loading font file";
	}

	simpleRectangle.setSize(sf::Vector2f(width, height));
	simpleRectangle.setFillColor(sf::Color::Red);
	simpleRectangle.setOrigin(width / 2, height / 2);
	simpleRectangle.setPosition(xPosition, yPosition);
	
	for (int i = 0; i < BLOCKS_NUM; i++)
	{
		levelWalls[i].setSize(wallSize);
		levelWalls[i].setPosition(x, y);
		x += wallSize.x;
		if ((i + 1) % 10 == 0)
		{
			y -= wallSize.y;
			x = 0.f;
		}
		if (i % 10 == 0 && (i / 10) % 2 == 0)
		{
			levelWalls[i].setFillColor(sf::Color::Blue);
		}
		else
		{
			levelWalls[i].setFillColor(sf::Color::White);
		}

	}

	for (int i = 0; i < NUM_PROJECTILES; i++)
	{
		projectiles[i].setSize(sf::Vector2f(projectileSize.x, projectileSize.y));
		projectiles[i].setOrigin(sf::Vector2f(projectileSize.x / 2, projectileSize.y / 2));
		projectiles[i].setFillColor(sf::Color::Yellow);
		projectiles[i].setPosition(xPosition, yPosition);
	}

#ifdef TEST_FPS
	x_updateFPS.setFont(m_arialFont);
	x_updateFPS.setPosition(20, 300);
	x_updateFPS.setCharacterSize(24);
	x_updateFPS.setFillColor(sf::Color::White);
	x_drawFPS.setFont(m_arialFont);
	x_drawFPS.setPosition(20, 350);
	x_drawFPS.setCharacterSize(24);
	x_drawFPS.setFillColor(sf::Color::White);
#endif
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asMilliseconds()); //60 fps
#ifdef TEST_FPS
			x_secondTime += timePerFrame;
			x_updateFrameCount++;
			if (x_secondTime.asSeconds() > 1)
			{
				std::string updatesPS = "UPS " + std::to_string(x_updateFrameCount - 1);
				x_updateFPS.setString(updatesPS);
				std::string drawsPS = "DPS " + std::to_string(x_drawFrameCount);
				x_drawFPS.setString(drawsPS);
				x_updateFrameCount = 0;
				x_drawFrameCount = 0;
				x_secondTime = sf::Time::Zero;
			}
#endif
		}
		render(); // as many as possible
#ifdef TEST_FPS
		x_drawFrameCount++;
#endif
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		xPosition -= speed;
		projectilePosition.x = xPosition;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xPosition += speed;
		projectilePosition.x = xPosition;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		shooting = true;
	}
}

void Game::moveDown()
{
	if (y > ScreenSize::s_height-100)
		return;
	y += 10 * wallSize.y+wallSpeed;
	x = 0.f;
	for (int i = 0; i < BLOCKS_NUM; i++)
	{
		levelWalls[i].setPosition(x, y);
		x += wallSize.x;
		if ((i + 1) % 10 == 0)
		{
			y -= wallSize.y;
			x = 0.f;
		}
	}
}

bool Game::collision()
{
	for (int i = 0; i < BLOCKS_NUM; i++)
	{
		if (levelData[i] == 1)
		{
			if (levelWalls[i].getGlobalBounds().intersects(simpleRectangle.getGlobalBounds()))
			{
				return true;
			}
		}
	}
	return false;
}

void Game::shoot()
{
	if (activeBullets < 10)
	{
		for (int i = 0; i <= activeBullets; i++)
		{
			projectilePosition.y = projectiles[i].getPosition().y;
			projectiles[i].setPosition(projectilePosition.x, projectilePosition.y - 5);
		}
		activeBullets++;
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	simpleRectangle.setPosition(xPosition, yPosition);
	if (!collision())
	{
		moveDown();
	}
	if (shooting)
	{
		shoot();
	}
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	for (int index = 0; index < BLOCKS_NUM; index++)
	{
		if (levelData[index] == 1)
		{
			m_window.draw(levelWalls[index]);
		}
	}
	for (int i = 0; i < activeBullets; i++)
	{
		m_window.draw(projectiles[i]);
	}
	m_window.draw(simpleRectangle);

#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}





