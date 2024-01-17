#pragma once
#include "Globals.h"

class Food
{
public:
	Food();
	void initialise(bool cherry, int x);
	sf::CircleShape getBody();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_position;
	bool isCherry;

};