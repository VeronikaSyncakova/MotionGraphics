
#ifndef GAME_HPP
#define GAME_HPP
#include "Player.h"
#include"Food.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialise();
	void setupFood();
	void drawFood();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	sf::RectangleShape topLine;
	sf::RectangleShape bottomLine;

	Player pacman;
	std::vector<Food> foodVector;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

