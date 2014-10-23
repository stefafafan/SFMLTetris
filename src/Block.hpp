#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Entity.hpp"
#include "Helpers.hpp"
#include "Globals.hpp"

class Block : public Entity
{
private:
	float x;
	float y;
	blockcoord coordinates;
	unsigned int type;

public:
	Block():x(floor(constants::bdWidth/2)), y(0) { generateBlock(); }
	
	auto generateBlock() -> void;
	
	auto right() -> int;
	auto left() -> int;
	auto top() -> int;
	auto bottom() -> int;
	
	auto getColor() -> sf::Color { return constants::blockcolors.at(type); }
	
	auto move(int incx, int incy) -> bool;
	auto rotate() -> void;

	auto placeBoard() -> void;
	auto isColliding() -> bool;

	auto isOverflow() -> bool;

	auto draw(sf::RenderWindow& wnd) -> void override 
	{
		for (auto coord : coordinates)
		{
			drawSingleBlock(wnd, getColor(), sf::Color::Black, coord.first+x, coord.second+y);
		}
	}
};

#endif