#include "Map.h"

Map::Map()
	: vertices(sf::PrimitiveType::Triangles),
	  grid{},
	  startPos(0, 0),
	  finishPos(gbl::MAP::ROWS -1, gbl::MAP::COLUMNS-1)
{
	vertices.resize(gbl::MAP::ROWS * gbl::MAP::COLUMNS * 6);

	for (size_t i = 0; i < this->grid.size(); i++)
	{
		for (size_t j = 0; j < this->grid[i].size(); j++)
		{
			float x = gbl::MAP::MARGIN + j * (gbl::MAP::CELL_SIZE + gbl::MAP::GAP);
			float y = gbl::MAP::MARGIN + i * (gbl::MAP::CELL_SIZE + gbl::MAP::GAP);
			float s = gbl::MAP::CELL_SIZE;

			// index prvního vrcholu této buòky
			size_t idx = (i * gbl::MAP::COLUMNS + j) * 6;
			// první trojúhelník
			vertices[idx + 0].position = sf::Vector2f(x, y);
			vertices[idx + 1].position = sf::Vector2f(x + s, y);
			vertices[idx + 2].position = sf::Vector2f(x + s, y + s);

			// druhý trojúhelník
			vertices[idx + 3].position = sf::Vector2f(x, y);
			vertices[idx + 4].position = sf::Vector2f(x + s, y + s);
			vertices[idx + 5].position = sf::Vector2f(x, y + s);
		}
	}
}

Map::~Map()
{
}

void Map::drawGrid(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->grid.size(); i++)
	{
		for (size_t j = 0; j < this->grid[i].size(); j++)
		{
			gbl::MAP::Cell& cell = this->grid[i][j];
			sf::Color col;
			switch (cell) {
			case gbl::MAP::Cell::Empty:
				col = sf::Color::White;
				break;
			case gbl::MAP::Cell::Wall:
				col = sf::Color::Blue;
				break;
			case gbl::MAP::Cell::Visited:
				col = sf::Color::Cyan;
				break;
			case gbl::MAP::Cell::Path:
				col = sf::Color::Magenta;
				break;
			}
			if (sf::Vector2i(i, j) == startPos)
				col = sf::Color::Green;
			else if (sf::Vector2i(i, j) == finishPos)
				col = sf::Color::Red;

			size_t idx = (i * gbl::MAP::COLUMNS + j) * 6;
			vertices[idx + 0].color = col;
			vertices[idx + 1].color = col;
			vertices[idx + 2].color = col;
			vertices[idx + 3].color = col;
			vertices[idx + 4].color = col;
			vertices[idx + 5].color = col;
		}
	}
	target.draw(vertices);
}

void Map::clearGrid()
{
	for (size_t i = 0; i < this->grid.size(); i++)
	{
		for (size_t j = 0; j < this->grid[i].size(); j++)
		{
			this->grid[i][j] = gbl::MAP::Cell::Empty;
		}
	}
}

gbl::MAP::Cell& Map::getCellAtCoords(sf::Vector2i& pos)
{
	if (pos.x >= 0 and pos.x < gbl::MAP::ROWS and pos.y >= 0 and pos.y < gbl::MAP::COLUMNS)
		return this->grid[pos.x][pos.y];
	gbl::MAP::Cell l = gbl::MAP::Cell::Invalid;
	return l;
}
