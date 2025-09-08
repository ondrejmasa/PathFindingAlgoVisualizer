#pragma once
#include <array>
#include <SFML/Graphics.hpp>

namespace gbl
{
	namespace SCREEN
	{
		constexpr unsigned int HEIGHT = 720;
		constexpr unsigned int WIDTH = 1280;
	}

	namespace MAP
	{
		constexpr unsigned char CELL_SIZE = 12;
		constexpr unsigned char GAP = 2;
		constexpr unsigned char MARGIN = 10;
		constexpr unsigned char ROWS = 50;
		constexpr unsigned char COLUMNS = 70;
		enum Cell
		{
			Empty,
			Wall,
			Invalid,
			Path,
			Visited
		};
	}

	namespace PATHFINDING
	{
		constexpr unsigned short CHECKS_PER_FRAME = 5;
	}

	using Grid = std::array<std::array<MAP::Cell, MAP::COLUMNS>, MAP::ROWS>;

	template <typename value_type>
	char sign(const value_type i_value)
	{
		return (0 < i_value) - (0 > i_value);
	}


	struct Vector2iLess {
		bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
			return a.x < b.x || (a.x == b.x && a.y < b.y);
		}
	};
}