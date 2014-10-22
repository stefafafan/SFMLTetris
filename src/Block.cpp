#include "Block.hpp"
#include <random>

auto Block::generateBlock() -> void
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 6);
	type = dis(gen);
	coordinates = blocks.at(type);
}

auto Block::move(int incx, int incy) -> void
{
	if ((left() + x + incx >= 1) && (right() + x + incx <= bdWidth+1))
	{
		x += incx;
	}
	if ((top() + y + incy >= 0) && (bottom() + y + incy <= bdHeight))
	{
		y += incy;
	}
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
}
