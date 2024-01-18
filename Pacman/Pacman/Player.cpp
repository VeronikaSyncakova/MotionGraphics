#include "Player.h"

Player::Player():m_position(sf::Vector2f(100.0f,225.0f)), m_right(true)
{
	m_body.setSize(sf::Vector2f(BODY_WIDTH, BODY_HEIGHT));
	m_body.setPosition(m_position);
}

sf::RectangleShape Player::getBody() const
{
	return m_body;
}

void Player::move()
{
	if (m_right)
	{
		m_position.x += PLAYER_SPEED;
		if (m_position.x + BODY_WIDTH > 700)
		{
			m_position.x = 100;
		}
	}
	else
	{
		m_position.x -= PLAYER_SPEED;
		if (m_position.x < 100)
		{
			m_position.x = 700- BODY_WIDTH;
		}
	}
	m_body.setPosition(m_position);
}

void Player::changeDirection()
{
	if (m_right)
	{
		m_right = false;
	}
	else
	{
		m_right = true;
	}
}

float Player::getPositionX()
{
	return m_position.x;
}

void Player::reset()
{
	m_position.x = 100;
	m_body.setPosition(m_position);
	m_right = true;
}

