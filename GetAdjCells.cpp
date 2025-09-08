#include "GetAdjCells.h"

std::vector<sf::Vector2i> getAdjCells(gbl::Grid& grid, sf::Vector2i& pos)
{
	std::vector<sf::Vector2i> result{};
	for (short i = -1; i <= 1; i++)
	{
		for (short j = -1; j <= 1; j++)
		{
			if (abs(i) + abs(j) == 1)

			{
				if (pos.x + i >= 0 and pos.x + i < gbl::MAP::ROWS and pos.y + j >= 0 and pos.y + j  < gbl::MAP::COLUMNS)
				{
					if (grid[pos.x+i][pos.y+j] == gbl::MAP::Cell::Empty)
					{
						result.push_back(sf::Vector2i(pos.x + i, pos.y + j));
					}
				}
			}
		}
	}
	return result;
}

