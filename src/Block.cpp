#include "Block.hpp"
#include <random>
#include <algorithm>

auto Block::generateBlock() -> void
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 6);
	type = dis(gen);
	coordinates = constants::blocks.at(type);
}

auto Block::right() -> int
{
	auto max = (*std::max_element(coordinates.begin(), coordinates.end(), [](auto c1, auto c2){ return c1.first < c2.first; })).first;
	return max;
}

auto Block::left() -> int
{
	auto min = (*std::min_element(coordinates.begin(), coordinates.end(), [](auto c1, auto c2){ return c1.first < c2.first; })).first;
	return min;
}

auto Block::top() -> int
{
	auto min = (*std::min_element(coordinates.begin(), coordinates.end(), [](auto c1, auto c2){ return c1.second < c2.second; })).second;
	return min;
}

auto Block::bottom() -> int
{
	auto max = (*std::max_element(coordinates.begin(), coordinates.end(), [](auto c1, auto c2){ return c1.second < c2.second; })).second;
	return max;
}

auto Block::move(int incx, int incy) -> bool
{
	auto canMove = false;
	x += incx;
	if (isColliding())
	{
		x -= incx;
	}
	y += incy;
	canMove = true;
	if (isColliding())
	{
		y -= incy;
		canMove = false;
	}
	return canMove;
}

auto Block::rotate() -> void
{
	for (auto &coord : coordinates)
	{
		auto tempx = coord.first;
		auto tempy = coord.second;
		coord.first = tempy;
		coord.second = 1-tempx;
	}
	if (isColliding())
	{
		for (auto &coord : coordinates)
		{
			auto tempx = coord.first;
			auto tempy = coord.second;
			coord.first = 1-tempy;
			coord.second = tempx;
		}
	}
}

auto Block::placeBoard() -> void
{
	for (auto coord : coordinates)
	{
		board.at(coord.second+y).at(coord.first+x) = type;
	}
}

auto Block::isColliding() -> bool
{
	auto colliding = false;
	for (auto coord : coordinates)
	{
		switch (board.at(coord.second+y).at(coord.first+x))
		{
			case 7:
			case 9:
				break;
			default:
				colliding = true;
				break;
		}
	}
	return colliding;
}

auto Block::isOverflow() -> bool
{
	return (top() + y) <= 0;
}