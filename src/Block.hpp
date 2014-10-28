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
	bool isGhost;

public:
	Block(unsigned int t):x(floor(constants::bdWidth/2)), y(0), type(t), isGhost(false)
	{
		coordinates = constants::blocks.at(type);
	}
	
	auto setGhost(bool flag) -> void;
	
	auto right() -> int;
	auto left() -> int;
	auto top() -> int;
	auto bottom() -> int;
	
	auto getColor() -> sf::Color { return constants::blockcolors.at(type); }
	auto getType() -> unsigned int { return type; }
	
	auto move(int incx, int incy) -> bool;
	auto drop() -> void;
	auto rotate(bool reverse) -> void;

	auto placeBoard() -> void;
	auto isColliding() -> bool;

	auto placeScreen(int newx, int newy) -> void;
	auto isOverflow() -> bool;
	auto startedFalling() -> bool;

	auto draw(sf::RenderWindow& wnd) -> void override 
	{
		auto color = getColor();
		if (isGhost)
		{
			color.a = 128;
		}
		for (auto coord : coordinates)
		{
			drawSingleBlock(wnd, color, sf::Color::Black, floor(coord.first+x), floor(coord.second+y));
		}
	}
};

#endif