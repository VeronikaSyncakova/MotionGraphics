//Veronika Syncakova c00288340

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
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>
#include <string>
#include <fstream>

enum class ButtonState { READY, OVER, DOWN };


class MenuButton
{
public:
	sf::RectangleShape shape;
	sf::Text text;
	ButtonState state = ButtonState::READY;
	sf::Vector2f downPos;
	sf::Vector2f readyPos;
	sf::Sound click;
	bool pressed = false;
	sf::Color curFillColor;


	void Init(sf::Vector2f pos, sf::Font& font, sf::Sound& sound)
	{
		click = sound;
		pressed = false;
		readyPos = pos;
		curFillColor = sf::Color::Blue;
		downPos = sf::Vector2f(pos.x - 10, pos.y + 10);
		shape.setSize(sf::Vector2f(250, 100));
		shape.setPosition(pos);

		text.setFont(font);
		UpdateUI();

	}
	void UpdateUI()
	{
		text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
		text.setPosition(shape.getPosition().x+(shape.getGlobalBounds().width/2.f), shape.getPosition().y+(shape.getGlobalBounds().height/2.f));

		shape.setFillColor(curFillColor);
	}

	void Update(sf::RenderWindow& window)
	{
		pressed = false;
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (state == ButtonState::READY)
		{
			shape.setPosition(readyPos);
			curFillColor = sf::Color::Blue;
			if (shape.getGlobalBounds().contains(mousePos))
			{

				state = ButtonState::OVER;
			}

		}
		if (state == ButtonState::OVER)
		{
			curFillColor = sf::Color::Green;

			if (shape.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					state = ButtonState::DOWN;
				}
			}
			else
			{
				state = ButtonState::READY;
			}
		}

		if (state == ButtonState::DOWN)
		{
			curFillColor = sf::Color::Magenta;
			shape.setPosition(downPos);
			if (shape.getGlobalBounds().contains(mousePos))
			{
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					state = ButtonState::READY;
					pressed = true;
					click.play();
				}
			}
			else
			{
				state = ButtonState::READY;
			}
		}

		UpdateUI();
	}
};

class Game
{
public:
	float randomNum;
	sf::RectangleShape playerShape;
	sf::RenderWindow* window;

	sf::RectangleShape colors[6];
	sf::RectangleShape colorsBackg;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Texture m_tileTexture;
	sf::Sprite m_tiles;

	bool jumping = false;
	bool turn = false;
	bool reachedEnd = false;

	int loadedLevel = 0;

	int chosenTile = 0;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	//animation
	float m_frameCounter = 0.0f; //which frame
	float m_frameIncrement = 0.2f; // speed of animation
	int m_frame = 0; //chooses frame
	int m_currentFrame{ -1 };

	static const int numRows = 20;
	static const int numCols = 45;

	int levelDataH[numRows][numCols] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 4, 1, 1, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 3,},
		{0, 0, 0, 0, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{1, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 4, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	};

	sf::RectangleShape levelH[numRows][numCols];
	sf::Sprite tiles[numRows][numCols];

	Game(sf::RenderWindow& t_window):window(&t_window)
	{
		if (!m_texture.loadFromFile("ASSETS/IMAGES/playerSpritesheet.png"))
		{
			std::cout << "could not load player spritesheet\n";
		}
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, 80, 100));
		m_sprite.setOrigin(40, 0);
		m_sprite.setScale(0.5f, 0.5f);

		if (!m_tileTexture.loadFromFile("ASSETS/IMAGES/tiles.png"))
		{
			std::cout << "could not load player tile spritesheet\n";
		}
	}
	void init()
	{
		playerShape.setSize(sf::Vector2f(20, 50));
		playerShape.setOrigin(10, 0);
		playerShape.setPosition(160, 500);
		turn = false;
		reachedEnd = false;

		//setup horizontal levelData
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				tiles[row][col].setTexture(m_tileTexture);
				if (levelDataH[row][col] == 1)
				{
					levelH[row][col].setFillColor(sf::Color::Red);
					tiles[row][col].setTextureRect(sf::IntRect(0, 0, 70, 30));
				}
				else if (levelDataH[row][col] == 0)
				{
					levelH[row][col].setFillColor(sf::Color::Black);
					tiles[row][col].setTextureRect(sf::IntRect(0, 150, 70, 30));
				}
				else if (levelDataH[row][col] == 2)
				{
					levelH[row][col].setFillColor(sf::Color::Blue);
					tiles[row][col].setTextureRect(sf::IntRect(0, 120, 70, 30));

				}
				else if (levelDataH[row][col] == 3)//final tile
				{
					levelH[row][col].setFillColor(sf::Color::Green);
					tiles[row][col].setTextureRect(sf::IntRect(0, 90, 70, 30));

				}
				else if (levelDataH[row][col] == 4) //jump
				{
					levelH[row][col].setFillColor(sf::Color::Cyan);
					tiles[row][col].setTextureRect(sf::IntRect(0, 60, 70, 30));
				}
				else if (levelDataH[row][col] == 5) //turn
				{
					levelH[row][col].setFillColor(sf::Color::Magenta);
					tiles[row][col].setTextureRect(sf::IntRect(0, 30, 70, 60));
				}
				levelH[row][col].setSize(sf::Vector2f(70, 30));
				levelH[row][col].setPosition(col * 70, row * 30);
				levelH[row][col].setOutlineColor(sf::Color::Transparent);
			}
		}
	}

	void run()
	{
		if (!reachedEnd)
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					if (!turn)
						levelH[row][col].move(-3.7, 0);
					else
						levelH[row][col].move(3.7, 0);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
		{
			velocityY = -12;
			jumping = true;
		}

		velocityY = velocityY + gravity;
		playerShape.move(0, velocityY);
		m_sprite.setPosition(playerShape.getPosition());

		gravity = 0.6;

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (velocityY >= 0)
				{
					if (levelDataH[row][col] == 1)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < levelH[row][col].getPosition().y)
							{
								gravity = 0;
								velocityY = 0;
								jumping = false;
								playerShape.setPosition(playerShape.getPosition().x, levelH[row][col].getPosition().y);
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								break;
							}
							else {
								init();
							}
						}
					}

					if (levelDataH[row][col] == 4)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < levelH[row][col].getPosition().y)
							{
								gravity = 0.6f;
								velocityY = -16.f;
								jumping = true;
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								break;
							}
							else {
								init();
							}
						}
					}
					if (levelDataH[row][col] == 3)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < levelH[row][col].getPosition().y)
							{
								gravity = 0.f;
								velocityY = 0.f;
								jumping = false;
								playerShape.setPosition(playerShape.getPosition().x, levelH[row][col].getPosition().y);
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								reachedEnd = true;
								break;
							}
							else {
								init();
							}
						}
					}
					if (levelDataH[row][col] == 5)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < levelH[row][col].getPosition().y)
							{
								gravity = 0.f;
								velocityY = 0.f;
								jumping = false;
								playerShape.setPosition(playerShape.getPosition().x, levelH[row][col].getPosition().y);
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								turn = !turn;
								break;
							}
							else {
								turn = false;
								init();
							}
						}
					}
				}

				if (velocityY < 0) //if jumping
				{
					if (levelDataH[row][col] == 1)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							init();
						}
					}
				}

				if (levelDataH[row][col] == 2)
				{
					if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
					{
						init();
					}
				}
			}
		}

		if (playerShape.getPosition().y > 600)
		{
			init();
		}

		//player animation
		m_frameCounter += m_frameIncrement;
		m_frame = static_cast<int>(m_frameCounter);
		if (velocityY < 0)
		{
			if (m_frame > 4 - 1)
			{
				m_frame = 3;
				m_frameCounter = 3.f;
			}
			if (m_frame != m_currentFrame)
			{
				m_currentFrame = m_frame;
				m_sprite.setTextureRect(sf::IntRect(m_frame * 80, 100, 80, 100));
			}
		}
		else if (velocityY == 0 && jumping)
		{
			m_frame = 4;
			m_currentFrame = m_frame;
			m_sprite.setTextureRect(sf::IntRect(m_frame * 80, 100, 80, 100));
		}
		else if (!jumping)
		{
			if (m_frame > 8 - 1)
			{
				m_frame = 0;
				m_frameCounter -= 8.0f;
			}
			if (m_frame != m_currentFrame)
			{
				m_currentFrame = m_frame;
				m_sprite.setTextureRect(sf::IntRect(m_frame * 80, 0, 80, 100));
			}
		}

		m_sprite.setPosition(playerShape.getPosition());
		
		if (turn)
			m_sprite.setScale(-0.5f, 0.5f);
		else
			m_sprite.setScale(0.5f, 0.5f);

		//Drawing
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				tiles[row][col].setPosition(levelH[row][col].getPosition());
				//window->draw(levelH[row][col]);
				window->draw(tiles[row][col]);
			}
		}

		window->draw(m_sprite);
		//window->draw(playerShape);
	}

	void editInit()
	{
		colorsBackg.setSize(sf::Vector2f(50.f, 190.f));
		colorsBackg.setFillColor(sf::Color(255, 255, 255, 150));
		colorsBackg.setPosition(750.f, 0.f);
		for (int i = 0; i < 6; i++)
		{
			colors[i].setSize(sf::Vector2f(35, 25));
			colors[i].setPosition(800 - 35, 30 * i);
			colors[i].setOutlineThickness(2.f);
			colors[i].setOutlineColor(sf::Color::Transparent);
		}
		colors[0].setFillColor(sf::Color::Black);
		colors[1].setFillColor(sf::Color::Red);
		colors[2].setFillColor(sf::Color::Blue);
		colors[3].setFillColor(sf::Color::Green);
		colors[4].setFillColor(sf::Color::Cyan);
		colors[5].setFillColor(sf::Color::Magenta);

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				//tiles[row][col].setTexture(m_tileTexture);
				levelH[row][col].setOutlineColor(sf::Color::White);
				levelH[row][col].setOutlineThickness(1.0f);
				if (levelDataH[row][col] == 1)
				{
					levelH[row][col].setFillColor(sf::Color::Red);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 0, 70, 30));
				}
				else if (levelDataH[row][col] == 0)
				{
					levelH[row][col].setFillColor(sf::Color::Black);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 150, 70, 30));
				}
				else if (levelDataH[row][col] == 2)
				{
					levelH[row][col].setFillColor(sf::Color::Blue);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 120, 70, 30));

				}
				else if (levelDataH[row][col] == 3)//final tile
				{
					levelH[row][col].setFillColor(sf::Color::Green);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 90, 70, 30));

				}
				else if (levelDataH[row][col] == 4) //jump
				{
					levelH[row][col].setFillColor(sf::Color::Cyan);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 60, 70, 30));
				}
				else if (levelDataH[row][col] == 5) //turn
				{
					levelH[row][col].setFillColor(sf::Color::Magenta);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 30, 70, 60));
				}
				levelH[row][col].setSize(sf::Vector2f(70, 30));
				levelH[row][col].setPosition(col * 70, row * 30);
			}
		}
	}

	void updateTile()
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				//tiles[row][col].setTexture(m_tileTexture);
				levelH[row][col].setOutlineColor(sf::Color::White);
				levelH[row][col].setOutlineThickness(1.0f);
				if (levelDataH[row][col] == 1)
				{
					levelH[row][col].setFillColor(sf::Color::Red);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 0, 70, 30));
				}
				else if (levelDataH[row][col] == 0)
				{
					levelH[row][col].setFillColor(sf::Color::Black);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 150, 70, 30));
				}
				else if (levelDataH[row][col] == 2)
				{
					levelH[row][col].setFillColor(sf::Color::Blue);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 120, 70, 30));

				}
				else if (levelDataH[row][col] == 3)//final tile
				{
					levelH[row][col].setFillColor(sf::Color::Green);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 90, 70, 30));

				}
				else if (levelDataH[row][col] == 4) //jump
				{
					levelH[row][col].setFillColor(sf::Color::Cyan);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 60, 70, 30));
				}
				else if (levelDataH[row][col] == 5) //turn
				{
					levelH[row][col].setFillColor(sf::Color::Magenta);
					//tiles[row][col].setTextureRect(sf::IntRect(0, 30, 70, 60));
				}
			}
		}
	}

	void edit()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					levelH[row][col].move(3.f, 0);
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					levelH[row][col].move(-3.f, 0);
				}
			}
		}
		
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
		if (pos.x > 700 && pos.y < 180)
		{
			for (int i = 0; i < 6; i++)
			{
				if (colors[i].getGlobalBounds().contains(pos))
				{
					colors[i].setOutlineColor(sf::Color::Yellow);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						chosenTile = i;
				}
				else if(i!=chosenTile)
				{
					colors[i].setOutlineColor(sf::Color::Transparent);
				}
			}
		}
		
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (pos.x >= 750.f && pos.y <= 190.f)
				{
				}
				else if(levelH[row][col].getGlobalBounds().contains(pos))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						levelDataH[row][col] = chosenTile;
						updateTile();
					}
				}

				//tiles[row][col].setPosition(levelH[row][col].getPosition());
				window->draw(levelH[row][col]);
				//window.draw(tiles[row][col]);
			}
		}
		window->draw(colorsBackg);
		for (int i = 0; i < 6; i++)
		{
			window->draw(colors[i]);
		}

	}

	void loadLevelData(int level)
	{
		loadedLevel = level;
		std::string chosenLevel = std::to_string(level);
		std::string line;
		std::ifstream myfile("level"+chosenLevel+".txt");
		int rowCounter = 0;
		int columCounter = 0;
		if (myfile.good())
		{
			while (std::getline(myfile, line))
			{
				for (int i = 0; i < line.length(); i++)
				{
					// line.at(i) returns char at position i in string. 
					char c = line.at(i);
					//std::cout << c;
					if (c >= '0' && c <= '9')
					{
						levelDataH[rowCounter][columCounter] = ((int)c - 48);
						//std::cout << levelDataH[rowCounter][columCounter] << ",";
						columCounter++;
					}
				}
				columCounter = 0;
				rowCounter++;
				//std::cout << std::endl;
			}
			myfile.close();
		}
		else
		{
			std::cout << "Unable to open file";
		}
	}

	void saveLevelData()
	{
		std::string chosenLevel = std::to_string(loadedLevel);
		std::string line;
		std::ofstream outputFile("level"+chosenLevel+".txt"); // create a new output file or overwrite an existing one

		if (outputFile.is_open()) { // check if the file was opened successfully
			for (int row = 0; row < numRows; row++)
			{
				outputFile << "{";
				for (int col = 0; col < numCols; col++)
				{
					outputFile << std::to_string(levelDataH[row][col]) << ", ";
				}
				if(row!=numRows)
					outputFile << "},\n";
				else
					outputFile << "},";
			}
			outputFile.close(); // close the file when done
			std::cout << "Data was written to output.txt\n";
		}
		else {
			std::cerr << "Error opening file\n";
		}

	}
};

enum class GameState { MENU, GAMEPLAY, EXIT, LOAD, LEADERBOARD, PAUSE, EDIT };

int main()
{
	GameState gameState = GameState::MENU;
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Menus");
	Game game(window);
	game.editInit();

	sf::Music music;
	if (!music.openFromFile("8bitretro.ogg"))
		return -1;
	music.play();
	music.setVolume(10);

	sf::Font font;
	font.loadFromFile("ASSETS/FONTS/ariblk.ttf");

	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile("click.ogg"))
		return -1;

	sf::Sound buttonClickSound;
	buttonClickSound.setBuffer(soundBuffer);

	srand(time(NULL));
	MenuButton MainMenuButtons[4];
	MenuButton GameBackButton;
	GameBackButton.Init(sf::Vector2f(0, 0), font, buttonClickSound);
	GameBackButton.text.setString("Menu");
	GameBackButton.text.setCharacterSize(12U);
	GameBackButton.shape.setSize(sf::Vector2f(70.f, 30.f));
	sf::Text gameText;
	gameText.setFont(font);
	gameText.setString("Coming Soon.....");
	gameText.setPosition(200, 300);
	for (int i = 0; i < 4; i++)
	{
		MainMenuButtons[i].Init(sf::Vector2f(300, 80 + (i * 110)), font, buttonClickSound);

	}
	MainMenuButtons[0].text.setString("Play");
	MainMenuButtons[1].text.setString("Edit");
	MainMenuButtons[2].text.setString("Exit");
	MainMenuButtons[3].text.setString("Load");
	sf::RectangleShape creature;
	creature.setSize(sf::Vector2f(10, 10));
	creature.setOrigin(5, 5);
	creature.setPosition(0, 0);
	creature.setFillColor(sf::Color::White);

	sf::RectangleShape target;
	target.setSize(sf::Vector2f(10, 10));
	target.setOrigin(5, 5);
	target.setPosition(400, 400);
	target.setFillColor(sf::Color::Green);

	MenuButton loadButtons[3];
	for (int i = 0; i < 3; i++)
	{
		loadButtons[i].Init(sf::Vector2f(150, 80 + (i * 100)), font, buttonClickSound);
	}
	loadButtons[0].text.setString("Level 1");
	loadButtons[1].text.setString("Level 2");
	loadButtons[2].text.setString("Level 3");

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Clock clock;
	clock.restart();


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			if (gameState == GameState::MENU)
			{
				for (int i = 0; i < 4; i++)
				{
					MainMenuButtons[i].Update(window);
				}

				if (MainMenuButtons[0].pressed == true)
				{
					music.pause();
					gameState = GameState::GAMEPLAY;
					game.init();
				}
				if (MainMenuButtons[1].pressed == true)
				{
					//std::cout << " 2 pressed" << std::endl;
					gameState = GameState::EDIT;
					game.editInit();
				}
				if (MainMenuButtons[2].pressed == true)
				{
					window.close();
					//std::cout << " 3 pressed" << std::endl;
				}
				if (MainMenuButtons[3].pressed == true)
				{
					gameState = GameState::LOAD;
					//std::cout << " 4 pressed" << std::endl;
				}

				window.clear(sf::Color::Black);

				for (int i = 0; i < 4; i++)
				{
					window.draw(MainMenuButtons[i].shape);
					window.draw(MainMenuButtons[i].text);
				}

				window.display();
			}

			if (gameState == GameState::GAMEPLAY)
			{
				GameBackButton.Update(window);
				if (GameBackButton.pressed == true)
				{
					music.play();
					gameState = GameState::MENU;
				}
				window.clear(sf::Color::Black);
				game.run();
				window.draw(GameBackButton.shape);
				window.draw(GameBackButton.text);
				//window.draw(gameText);
				window.display();
			}
			else if (gameState == GameState::EDIT)
			{
				GameBackButton.Update(window);
				if (GameBackButton.pressed == true)
				{
					music.play();
					game.saveLevelData();
					gameState = GameState::MENU;
				}
				window.clear(sf::Color::Black);
				game.edit();
				window.draw(GameBackButton.shape);
				window.draw(GameBackButton.text);
				window.display();
			}
			else if (gameState == GameState::LOAD)
			{
				window.clear(sf::Color::Black);

				GameBackButton.Update(window);
				if (GameBackButton.pressed == true)
				{
					music.play();
					gameState = GameState::MENU;
				}

				for (int i = 0; i < 3; i++)
				{
					loadButtons[i].Update(window);
					if (loadButtons[i].pressed == true)
					{
						game.loadLevelData(i+1);
						//game.init();
						//game.editInit();
						gameState = GameState::MENU;
					}
					window.draw(loadButtons[i].shape);
					window.draw(loadButtons[i].text);
				}

				window.draw(GameBackButton.shape);
				window.draw(GameBackButton.text);
				window.display();
			}
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}
