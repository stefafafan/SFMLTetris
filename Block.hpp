#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Entity.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <array>

class Block : public Entity
{
private:
	unsigned int type;
	std::array<sf::Color, 7> blockcolors = {{
		sf::Color(255, 0, 0),		// Red
		sf::Color(255, 240, 0),		// Yellow
		sf::Color(200, 30, 140),	// Purple
		sf::Color(50, 200, 50),		// Green
		sf::Color(255, 128, 0),		// Orange
		sf::Color(0, 0, 255),		// Blue
		sf::Color(0, 255, 255)		// Light Blue
	}};

public:
	float x;
	float y;
	blockcoord coordinates;
	Block():x(floor(bdWidth/2)), y(0)
	{
		generateBlock();
	}
	auto generateBlock() -> void;

	auto right() -> int
	{
		return coordinates.at(2).first;
	}
	auto left() -> int
	{
		return coordinates.at(0).first;
	}
	auto top() -> int
	{
		return 0;
	}
	auto bottom() -> int
	{
		return (type == 1) ? -1 : 0;
	}
	auto getColor() -> sf::Color { return blockcolors.at(type); }
	auto move(int incx, int incy) -> void;
	auto rotate() -> void;

	auto draw(sf::RenderWindow& wnd) -> void override 
	{
		for (auto coord : coordinates)
		{
			drawSingleBlock(wnd, getColor(), sf::Color::Black, coord.first+x, coord.second+y);
		}
	}
};

#endif