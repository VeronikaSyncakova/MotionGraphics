#pragma once
#include "Globals.h"

class Player
{
public:
	Player();
	sf::RectangleShape getBody() const;
	void move();
	void changeDirection();

private:
	sf::RectangleShape m_body;
	sf::Vector2f m_position;
	bool m_right;

};