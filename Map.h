#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Global.h"

class Map
{
private:
	sf::VertexArray vertices;

public:
	gbl::Grid grid;

	sf::Vector2i startPos;
	sf::Vector2i finishPos;

	Map();
	virtual ~Map();

	void drawGrid(sf::RenderTarget& target);

	void clearGrid();

	gbl::MAP::Cell& getCellAtCoords(sf::Vector2i& pos);
};

