#pragma once
#include "Globals.h"
#include "Player.h"

class Ghost
{
public:
	Ghost();
	void move(Player& player);
	sf::RectangleShape getBody() const;
	void cherryInfected();
	bool infected();
	void reset(Player& player);

private:
	sf::RectangleShape m_body;
	sf::Vector2f m_position;
	int ateCherry;

};