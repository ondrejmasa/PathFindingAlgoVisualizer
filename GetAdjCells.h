#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"

std::vector<sf::Vector2i> getAdjCells(gbl::Grid& grid, sf::Vector2i& pos);