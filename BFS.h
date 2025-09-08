#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <map>
#include "GetAdjCells.h"

bool bfsSearch(std::queue<sf::Vector2i>& pathQueue, sf::Vector2i& startPos, sf::Vector2i& finishPos, gbl::Grid& grid,
	std::map< sf::Vector2i, sf::Vector2i, gbl::Vector2iLess>& prevPos, unsigned short& pathLenght, sf::Sound& beepSound);

void BfsRestart(std::queue<sf::Vector2i>& pathQueue, sf::Vector2i& startPos, sf::Vector2i& finishPos, gbl::Grid& grid, std::map< sf::Vector2i, sf::Vector2i, gbl::Vector2iLess >& prevPos, unsigned short& pathLenght);