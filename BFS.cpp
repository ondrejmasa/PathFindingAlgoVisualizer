#include "BFS.h"
#include <iostream>


bool bfsSearch(std::queue<sf::Vector2i>& pathQueue, sf::Vector2i& startPos, sf::Vector2i& finishPos, gbl::Grid& grid,
	std::map< sf::Vector2i, sf::Vector2i, gbl::Vector2iLess >& prevPos, unsigned short& pathLenght, sf::Sound& beepSound)
{
	if (grid[startPos.x][startPos.y] != gbl::MAP::Cell::Visited)
	{
		pathQueue.push(startPos);
	}
	for (unsigned short a = 0; a < gbl::PATHFINDING::CHECKS_PER_FRAME; a++)
	{
		if (pathQueue.empty())
		{
			return false;
		}

		sf::Vector2i pos = pathQueue.front();
		std::vector<sf::Vector2i> adjCells = getAdjCells(grid, pos);

		float ratio = 1.f - 1.f * (abs(finishPos.x - pos.x) + abs(finishPos.y - pos.y)) / (gbl::MAP::COLUMNS + gbl::MAP::ROWS);
		beepSound.setPitch(0.1f + (ratio * 5.0f));
		std::cout << ratio << '\n';
		beepSound.play();

		pathQueue.pop();

		if (pos == finishPos)
		{
			sf::Vector2i pathPos = pos;
			do {
				grid[pathPos.x][pathPos.y] = gbl::MAP::Cell::Path;
				pathPos = prevPos.at(pathPos);
				++pathLenght;
			} while (pathPos != startPos);
			return true;
		}

		for (sf::Vector2i& c : adjCells)
		{
			grid[c.x][c.y] = gbl::MAP::Cell::Visited;
			prevPos[c] = pos;
			pathQueue.push(c);
		}
	}
	return false;
}

void BfsRestart(std::queue<sf::Vector2i>& pathQueue, sf::Vector2i& startPos, sf::Vector2i& finishPos, gbl::Grid& grid, std::map< sf::Vector2i, sf::Vector2i, gbl::Vector2iLess >& prevPos, unsigned short& pathLenght)
{
	std::queue<sf::Vector2i>().swap(pathQueue);
	pathQueue.push(startPos);
	prevPos.clear();

	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != gbl::MAP::Cell::Wall)
			{
				grid[i][j] = gbl::MAP::Cell::Empty;
			}
		}
	}

	pathLenght = 0u;
}