/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author Peter Lowe
/// @date May 2019
/// </summary>

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

void setupFood(sf::CircleShape t_circles[], int t_numCircles, int& t_cherryIndex)
{
	t_cherryIndex = rand() % 10;
	for (int index = 0; index < t_numCircles; index++)
	{
		if (index == t_cherryIndex)
		{
			t_circles[index].setFillColor(sf::Color::Green);
			t_circles[index].setRadius(15);
		}
		else
		{
			t_circles[index].setFillColor(sf::Color::White);
			t_circles[index].setRadius(10);
		}
		t_circles[index].setPosition(40 * index + 200, 100);
	}
}

bool allFoodEaten(sf::CircleShape t_circles[], int t_numCircles)
{
	int counter = 0;
	for (int index = 0; index < t_numCircles; index++)
	{
		if (t_circles[index].getPosition().x==1000)
		{
			counter++;
		}
	}
	if (counter == t_numCircles)
	{
		return true;
	}
	return false;
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman Extra");

	sf::RectangleShape topLineTop;
	sf::RectangleShape topLineBottom;
	topLineTop.setSize(sf::Vector2f(500, 5));
	topLineTop.setFillColor(sf::Color::White);
	topLineTop.setPosition(150, 80);
	topLineBottom.setSize(sf::Vector2f(500, 5));
	topLineBottom.setFillColor(sf::Color::White);
	topLineBottom.setPosition(150, 150);

	sf::RectangleShape simpleRectangle;
	sf::RectangleShape ghost;
	float width = 30;
	float height = 30;

	simpleRectangle.setSize(sf::Vector2f(width, height));
	simpleRectangle.setFillColor(sf::Color::Red);
	simpleRectangle.setPosition(100, 100);

	ghost.setSize(sf::Vector2f(width, height));
	ghost.setFillColor(sf::Color::Yellow);
	ghost.setPosition(600, 100);

	srand(time(NULL));

	//setup food
	const int numCircles = 10;
	int cherryIndex = 0;
	sf::CircleShape circles[numCircles];
	setupFood(circles, numCircles, cherryIndex);


	float xPosition = 150;//rand() % 800;
	float yPosition = 100;
	float speed = 2;
	float xPosGhost = 600;
	float yPosGhost = 100;
	float speedGhost = 1;
	float ghostTimer = 180;
	bool spacePressed = false;

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
		//handle input
		if (timeSinceLastUpdate > timePerFrame)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (spacePressed == false)
				{
					speed *= -1;
					spacePressed = true;
				}
			}
			else {
				spacePressed = false;
			}
			//change position of pacman
			xPosition += speed;
			if (xPosition < 150)
			{
				xPosition = 600;
			}
			else if (xPosition > 600)
			{
				xPosition = 150;
			}
			simpleRectangle.setPosition(xPosition, yPosition);

			//draw food off screen when eaten
			for (int index = 0; index < numCircles; index++)
			{
				if (simpleRectangle.getGlobalBounds().intersects(circles[index].getGlobalBounds()))
				{
					circles[index].setPosition(1000, 1000);
					//makes ghost eatable and slower
					if (index == cherryIndex)
					{
						ghostTimer = 0;
					}
				}
			}
			if (allFoodEaten(circles, numCircles))
			{
				setupFood(circles, numCircles, cherryIndex);
			}

			//change position of ghost
			if (ghostTimer < 180)
			{
				ghostTimer++;
				ghost.setFillColor(sf::Color::Blue);
				speedGhost = 0.5;
				if (xPosGhost > xPosition && xPosGhost<=600)
				{
					xPosGhost += speedGhost;
				}
				else if (xPosGhost < xPosition && xPosGhost >= 150)
				{
					xPosGhost -= speedGhost;
				}
			}
			else
			{
				ghost.setFillColor(sf::Color::Yellow);
				speedGhost = 1;
				if (xPosGhost > xPosition)
				{
					xPosGhost -= speedGhost;
				}
				else if (xPosGhost < xPosition)
				{
					xPosGhost += speedGhost;
				}
			}
			ghost.setPosition(xPosGhost, yPosGhost);

			//collision with ghost
			if (simpleRectangle.getGlobalBounds().intersects(ghost.getGlobalBounds()))
			{
				if (ghostTimer < 180)
				{
					if (xPosition < xPosGhost)
					{
						xPosGhost = 150;

					}
				}
				xPosGhost = 600;
				xPosition = 150;
				speed = 2;
				ghost.setPosition(xPosGhost, yPosGhost);
				simpleRectangle.setPosition(xPosition, yPosition);
			}
			//draw shapes
			window.clear();
			window.draw(topLineTop);
			window.draw(topLineBottom);
			for (int index = 0; index < numCircles; index++)
			{
				window.draw(circles[index]);
			}
			window.draw(ghost);
			window.draw(simpleRectangle);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}
