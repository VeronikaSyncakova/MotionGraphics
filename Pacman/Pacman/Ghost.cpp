#include "Ghost.h"

Ghost::Ghost() :m_position(sf::Vector2f(700.0f - BODY_WIDTH, 225.0f)), ateCherry(120)
{
	m_body.setSize(sf::Vector2f(BODY_WIDTH, BODY_HEIGHT));
	m_body.setPosition(m_position);
	m_body.setFillColor(sf::Color::Blue);
}

void Ghost::move(Player& player)
{
	if (ateCherry>=120)
	{
		if (player.getPositionX() > m_position.x)
		{
			m_position.x += GHOST_SPEED;
		}
		else if (player.getPositionX() < m_position.x)
		{
			m_position.x -= GHOST_SPEED;
		}
		m_body.setFillColor(sf::Color::Blue);
	}
	else
	{
		ateCherry++;
		if (player.getPositionX() > m_position.x)
		{
			m_position.x -= GHOST_SPEED/2.0f;
		}
		else if (player.getPositionX() < m_position.x)
		{
			m_position.x += GHOST_SPEED/2.0f;
		}
		m_body.setFillColor(sf::Color::Red);
	}
	m_body.setPosition(m_position);
}

sf::RectangleShape Ghost::getBody() const
{
	return m_body;
}

void Ghost::cherryInfected()
{
	ateCherry=0;
}

bool Ghost::infected()
{
	if (ateCherry >= 120)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Ghost::reset(Player& player)
{
	if (player.getPositionX() < 400)
	{
		m_position.x = 700 - BODY_WIDTH;
	}
	else
	{
		m_position.x = 100;
	}
	m_body.setPosition(m_position);
	ateCherry = 120;
}
