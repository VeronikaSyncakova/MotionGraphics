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
#include <iostream>
#include <time.h> 
#include <SFML/Audio.hpp>

class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;
	sf::RectangleShape playerShape;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_tileTexture;
	sf::Sprite m_tiles;

	sf::SoundBuffer m_jumpB;
	sf::SoundBuffer m_longJumpB;
	sf::SoundBuffer m_whoopB;
	sf::SoundBuffer m_endB;
	sf::SoundBuffer m_looseB;
	sf::SoundBuffer m_backgroundB;

	sf::Sound m_jumpS;
	sf::Sound m_longJumpS;
	sf::Sound m_whoopS;
	sf::Sound m_endS;
	sf::Sound m_looseS;
	sf::Sound m_backgroundS;


	float m_frameCounter = 0.0f; //which frame
	float m_frameIncrement = 0.2f; // speed of animation
	int m_frame = 0; //chooses frame
	int m_currentFrame{ -1 };

	bool jumping = false;
	bool turn = false;
	bool reachedEnd = false;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	int currentLevel = 1;


	static const int numRows = 45;
	static const int numCols = 20;
	int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//start
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },//
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 }, //
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 } }; //end

	/*
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 4, 0, 1, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	*/

	int levelDataH[numCols][numRows] =
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

	/* { { _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, 1, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, 1, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, 1, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, 1, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, 1, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, 1, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, 1, 1, _, _, 1, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, 1, _, _, 1, _, _, _, _, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, 1, _, _, _, 1, 1, 1, _, _, _, _, _, _, 1, _, 1, _, _, 1, 1, 1, 1, _, _, }
	{ _, _, _, _, _, _, _, _, _, _, 2, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, 1, _, _, _, _, _, _, _, 1, 1, _, _, _, 1, _, 1, _, _, _, _, }
	{ _, _, _, _, _, _, _, _, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, _, _, _, _, _, _, _, 1, _, _, _, 1, 1, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, }
	{ _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, }
	{ _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, 1, _, _, 1, 1, }
	{ _, _, _, _, _, 1, _, 2, _, 2, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, }
	{ 1, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, , 1, 1, 1, _, _, 3, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, }
	{ */

	int levelDataH2[numCols][numRows] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 4, 1, 1, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 1, 1, 1, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,},
		{0, 0, 0, 0, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{1, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 4, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	};

	sf::RectangleShape levelH[numCols][numRows];
	sf::Sprite tiles[numCols][numRows];

	//sf::RectangleShape level[numRows][numCols];


	Game()
	{
		window.create(sf::VideoMode(800, 600), "Endless Runner Game");
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
		
		if (!m_jumpB.loadFromFile("ASSETS/AUDIO/Jump.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_jumpS.setBuffer(m_jumpB);
		if (!m_longJumpB.loadFromFile("ASSETS/AUDIO/LongJump.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_jumpS.setBuffer(m_jumpB);
		if (!m_whoopB.loadFromFile("ASSETS/AUDIO/Whoop.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_whoopS.setBuffer(m_whoopB);
		if (!m_endB.loadFromFile("ASSETS/AUDIO/EndTile.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_endS.setBuffer(m_endB);
		if (!m_looseB.loadFromFile("ASSETS/AUDIO/StartAgain.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_looseS.setBuffer(m_looseB);
		if (!m_backgroundB.loadFromFile("ASSETS/AUDIO/Background.wav"))
		{
			std::cout << "could not load audio\n";
		}
		m_backgroundS.setBuffer(m_backgroundB);
		m_backgroundS.play();
		m_backgroundS.setLoop(true);
	}
	void init()
	{
		m_looseS.play();
		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 50));
		playerShape.setOrigin(10, 0);
		playerShape.setPosition(160, 500);
		turn = false;
		//turns the level data into horizontal form
		/*
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				levelDataH[col][row] = levelData[row][col];
			}
		}
		*/
		std::cout << "{{ ";
		//prints out the horizontal level data
		for (int row = 0; row < numCols; row++)
		{
			for (int col = 0; col < numRows; col++)
			{
				if(levelDataH[row][col]==0)
				{
					std::cout << "_";
				}
				else if(levelDataH[row][col] == 1)
				{
					std::cout << "1";
				}
				else if (levelDataH[row][col] == 2)
				{
					std::cout << "2";
				}
				else if (levelDataH[row][col] == 3)
				{
					std::cout << "3";
				}
				std::cout << ",";
			}
			std::cout << "} \n { ";

		}
		std::cout <<"/////////////////////////////////////////////////////" << std::endl;

		//setup horizontal levelData
		for (int row = 0; row < numCols; row++)
		{
			for (int col = 0; col < numRows; col++)
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
			}
		}

		/*
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Blue);

				}
			}
			//std::cout << std::endl;
		}*/

	}

	void initLevel2()
	{
		m_looseS.play();
		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 50));
		playerShape.setOrigin(10, 0);
		playerShape.setPosition(160, 500);
		turn = false;
		reachedEnd = false;
		std::cout << "{{ ";
		//prints out the horizontal level data
		for (int row = 0; row < numCols; row++)
		{
			for (int col = 0; col < numRows; col++)
			{
				if (levelDataH2[row][col] == 0)
				{
					std::cout << "_";
				}
				else if (levelDataH2[row][col] == 1)
				{
					std::cout << "1";
				}
				else if (levelDataH2[row][col] == 2)
				{
					std::cout << "2";
				}
				else if (levelDataH2[row][col] == 3)
				{
					std::cout << "3";
				}
				std::cout << ",";
			}
			std::cout << "} \n { ";

		}
		std::cout << "/////////////////////////////////////////////////////" << std::endl;

		//setup horizontal levelData
		for (int row = 0; row < numCols; row++)
		{
			for (int col = 0; col < numRows; col++)
			{
				tiles[row][col].setTexture(m_tileTexture);
				if (levelDataH2[row][col] == 1)
				{
					levelH[row][col].setFillColor(sf::Color::Red);
					tiles[row][col].setTextureRect(sf::IntRect(0, 0, 70, 30));
				}
				else if (levelDataH2[row][col] == 0)
				{
					levelH[row][col].setFillColor(sf::Color::Black);
					tiles[row][col].setTextureRect(sf::IntRect(0, 150, 70, 30));
				}
				else if (levelDataH2[row][col] == 2)
				{
					levelH[row][col].setFillColor(sf::Color::Blue);
					tiles[row][col].setTextureRect(sf::IntRect(0, 120, 70, 30));

				}
				else if (levelDataH2[row][col] == 3)//final tile
				{
					levelH[row][col].setFillColor(sf::Color::Green);
					tiles[row][col].setTextureRect(sf::IntRect(0, 90, 70, 30));

				}
				else if (levelDataH2[row][col] == 4) //jump
				{
					levelH[row][col].setFillColor(sf::Color::Cyan);
					tiles[row][col].setTextureRect(sf::IntRect(0, 60, 70, 30));
				}
				else if (levelDataH2[row][col] == 5) //turn
				{
					levelH[row][col].setFillColor(sf::Color::Magenta);
					tiles[row][col].setTextureRect(sf::IntRect(0, 30, 70, 60));
				}
				levelH[row][col].setSize(sf::Vector2f(70, 30));
				levelH[row][col].setPosition(col * 70, row * 30);
			}
		}

		/*
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Blue);

				}
			}
			//std::cout << std::endl;
		}*/

	}

	void level2()
	{
		for (int row = 0; row < numCols; row++)
		{
			for (int col = 0; col < numRows; col++)
			{
				if (velocityY >= 0)
				{
					if (levelDataH2[row][col] == 1)
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
								initLevel2();
							}
						}
					}
					if (levelDataH2[row][col] == 4)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < levelH[row][col].getPosition().y)
							{
								gravity = 0.6f;
								velocityY = -16.f;
								jumping = true;
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								m_longJumpS.play();
								break;
							}
							else {
								initLevel2();
							}
						}
					}
					if (levelDataH2[row][col] == 3)
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
								m_endS.play();
								break;
							}
							else {
								initLevel2();
							}
						}
					}
					if (levelDataH2[row][col] == 5)
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
								m_whoopS.play();
								break;
							}
							else {
								turn = false;
								initLevel2();
							}
						}
					}

				}
				if (velocityY < 0) //if jumping
				{
					if (levelDataH2[row][col] == 1)
					{

						if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
						{
							initLevel2();
						}

					}

				}
				if (levelDataH2[row][col] == 2)
				{

					if (playerShape.getGlobalBounds().intersects(levelH[row][col].getGlobalBounds()))
					{
						initLevel2();
					}

				}
			}
		}
	}

	void run()
	{
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
				if (!reachedEnd)
				{
					for (int row = 0; row < numCols; row++)
					{
						for (int col = 0; col < numRows; col++)
						{
							if(!turn)
								levelH[row][col].move(-3.7, 0);
							else
								levelH[row][col].move(3.7, 0);
						}
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					m_jumpS.play();
					if (reachedEnd)
					{
						initLevel2();
					}
					else
					{
						velocityY = -12;
						m_frameCounter = 0.f;
						jumping = true;
					}
				}

				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);
				m_sprite.setPosition(playerShape.getPosition());

				gravity = 0.6;

				if (currentLevel == 2)
				{
					level2();
				}
				else
				{
					for (int row = 0; row < numCols; row++)
					{
						for (int col = 0; col < numRows; col++)
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
											m_longJumpS.play();
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
											currentLevel = 2;
											m_endS.play();
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
											m_whoopS.play();
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

				}

				if (playerShape.getPosition().y > 600)
				{
					init();
				}

				m_sprite.setPosition(playerShape.getPosition());

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/// player animation
				if (turn)
					m_sprite.setScale(-0.5f, 0.5f);
				else
					m_sprite.setScale(0.5f, 0.5f);

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
				else if(!jumping)
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

				window.clear();

				for (int row = 0; row < numCols; row++)
				{
					for (int col = 0; col < numRows; col++)
					{
						tiles[row][col].setPosition(levelH[row][col].getPosition());
						//window.draw(levelH[row][col]);
						window.draw(tiles[row][col]);
					}
				}


				//window.draw(playerShape);
				window.draw(m_sprite);


				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	Game game;
	game.init();
	game.run();

	return 1; // success
}