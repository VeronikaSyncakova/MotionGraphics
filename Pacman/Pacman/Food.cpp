#include "Food.h"


Food::Food()
{
}

void Food::initialise(bool cherry, int x)
{
	isCherry = cherry;
	if (isCherry)
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
}

sf::CircleShape Food::getBody()
{
	return m_body;
}
