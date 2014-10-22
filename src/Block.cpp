#include "Block.hpp"
#include <random>
#include <algorithm>

auto Block::generateBlock() -> void
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 6);
	type = dis(gen);
	coordinates = blocks.at(type);
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

auto Block::move(int incx, int incy) -> void
{
	if ((left() + x + incx >= 1) && (right() + x + incx <= bdWidth))
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
