#pragma once
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Global.h"
#include "Map.h"
#include "BFS.h"


class Program
{
private:
	sf::RenderWindow* window;

	Map map;

	bool isMouseDown;
	sf::Vector2i mouseCoordStart;

	sf::Clock clock;
	int frameCount = 0;
	float fps = 0.0f;
	sf::Time timer = sf::Time::Zero;

	std::queue<sf::Vector2i> BFSQueue;
	std::map< sf::Vector2i, sf::Vector2i, gbl::Vector2iLess> BFSPrevPos;
	bool BFSFinished;
	bool BFSStart;
	unsigned short pathLength;

	bool mapUpdated;

	sf::Font font;
	std::optional<sf::Text> pathLenText;

	sf::SoundBuffer soundBuffer;
	sf::Sound beepSound;

	sf::Vector2i getCellCoords(sf::Vector2i pos);
	void initText();
	void renderText(sf::RenderTarget* target);
	void updateText();

	void initSounds();

	void initWindow();
	void pollEvents();
	void updateMapWalls();

	void restart();
	void startAgain();

public:
	Program();
	virtual ~Program();

	void run();
	void update();
	void render();
};

