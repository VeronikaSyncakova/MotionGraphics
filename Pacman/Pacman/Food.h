#pragma once
#include "Globals.h"

class Food
{
public:
	Food();
	void initialise(bool t_cherry, int x);
	sf::CircleShape getBody();
	bool collision(sf::RectangleShape t_body);
	void moveOffScreen();
	bool isOffScreen();
	bool isCherry();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_position;
	bool cherry;
	bool offScreen;

};