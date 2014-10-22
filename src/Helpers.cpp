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
