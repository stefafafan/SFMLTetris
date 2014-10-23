#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>

auto drawSingleBlock(sf::RenderWindow& wnd, sf::Color color, sf::Color border, float x, float y) -> void;
auto setupBackground() -> void;
auto drawBackground(sf::RenderWindow& wnd) -> void;
auto checkLines() -> void;
auto deleteLine(int linenum) -> void;

#endif