#include "Player.h"

Player::Player():m_position(sf::Vector2f(100.0f,225.0f)), m_right(true)
{
	m_body.setSize(sf::Vector2f(40.0f, 60.0f));
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
	}
	else
	{
		m_position.x -= PLAYER_SPEED;
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

