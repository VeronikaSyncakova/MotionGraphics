

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 


int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "First Graphics in C++");

	int levelData[] =
	{ 1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,0,1,1,
	1,1,1,1,1,1,0,0,1,1,
	1,1,1,1,1,1,0,0,0,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,0,0,0,1,1,1,1,
	1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1 };
	int const NUM_DATA = 100;

	sf::RectangleShape levelWalls[NUM_DATA];
	sf::Vector2f wallSize{80.f, 100.f};
	float wallSpeed = 5.f;
	float y = 600.f-wallSize.y;
	float x = 0.f;
	for (int i = 0; i < NUM_DATA; i++)
	{
		levelWalls[i].setSize(wallSize);
		levelWalls[i].setPosition(x,y);
		x += wallSize.x;
		if ((i+1) % 10 == 0)
		{
			y -= wallSize.y;
			x = 0.f;
		}
		if (i % 10 == 0 && (i/10) % 2 == 0)
		{
			levelWalls[i].setFillColor(sf::Color::Blue);
		}
		else
		{
			levelWalls[i].setFillColor(sf::Color::White);
		}
		
	}


	sf::RectangleShape simpleRectangle;
	float width = 30.f;
	float height = 30.f;
	float xPosition = 400.f;
	float yPosition = 550.f;
	float speed = 2.f;

	simpleRectangle.setSize(sf::Vector2f(width, height));
	simpleRectangle.setFillColor(sf::Color::Red);
	simpleRectangle.setPosition(100, 200);

	srand(time(NULL));

	int timer = 0;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clockForFrameRate;

	clockForFrameRate.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		timeSinceLastUpdate += clockForFrameRate.restart();


		if (timeSinceLastUpdate > timePerFrame)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				
				xPosition-= speed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				xPosition += speed;
			}
		}
			
		simpleRectangle.setPosition(xPosition, yPosition);

			window.clear();
			for (int index = 0; index < NUM_DATA; index++)
			{
				if (levelData[index] == 1)
				{
					window.draw(levelWalls[index]);
				}
			}
			window.draw(simpleRectangle);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		
	}

	return 0;
}
