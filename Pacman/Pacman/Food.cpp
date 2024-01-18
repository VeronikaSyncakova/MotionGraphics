#include "Food.h"


Food::Food()
{
}

void Food::initialise(bool t_cherry, int x)
{
	cherry = t_cherry;
	if (cherry)
	{
		m_body.setFillColor(sf::Color::Red);
		m_body.setRadius(20.0f);
		m_body.setOrigin(20.0f, 20.0f);
	}
	else 
	{
		m_body.setRadius(10.0f);
		m_body.setOrigin(10.0f,10.0f);
	}
	m_position = sf::Vector2f(x, 250.0f);
	m_body.setPosition(m_position);
	offScreen = false;
}

sf::CircleShape Food::getBody()
{
	return m_body;
}

bool Food::collision(sf::RectangleShape t_body)
{
	if (m_body.getGlobalBounds().intersects(t_body.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Food::moveOffScreen()
{
	m_position.x = 1000;
	m_body.setPosition(m_position);
	offScreen = true;
}

bool Food::isOffScreen()
{
	return offScreen;
}

bool Food::isCherry()
{
	return cherry;
}
