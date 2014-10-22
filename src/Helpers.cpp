#include "Helpers.hpp"
#include "Globals.hpp"

auto drawSingleBlock(sf::RenderWindow& wnd, sf::Color color, sf::Color border, float x, float y) -> void
{
	auto blockx = (constants::wndWidth/3.f)/(constants::bdWidth+2.f);
	auto blocky = constants::wndHeight/(constants::bdHeight+2.f);
	sf::RectangleShape shape;
	shape.setPosition((constants::wndWidth/3.f)+(x*blockx)+(blockx/2.f), (y*blocky)+(blocky/2.f));
	shape.setSize({blockx, blocky});
	shape.setFillColor(color);
	shape.setOutlineColor(border);
	shape.setOutlineThickness(-1.f);
	shape.setOrigin(blockx/2.f, blocky/2.f);
	wnd.draw(shape);
}

auto setupBackground() -> void
{
	auto midx = floor(constants::bdWidth/2);

	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(i).size(); ++j)
		{
			if (i == 0 && (midx - 2 <= j && j <= midx + 3))
			{
				board.at(i).at(j) = 9;  // Opening at top.
			}
			else if (j == 0 || j == constants::bdWidth+1 || i == 0 || i == constants::bdHeight+1)
			{

				board.at(i).at(j) = 8;  // Wall.
			}
			else
			{
				board.at(i).at(j) = 7;  // Nothing.
			}
		}
	}
}

auto drawBackground(sf::RenderWindow& wnd) -> void
{
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(i).size(); ++j)
		{
			drawSingleBlock(wnd, constants::blockcolors.at(board.at(i).at(j)), sf::Color::Black, j, i);
		}
	}
}
