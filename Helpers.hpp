#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <array>

constexpr int wndWidth{800}, wndHeight{450};
constexpr int bdWidth{10}, bdHeight{20};

using blockcoord = std::array<std::pair<int, int>, 4>;

constexpr std::array<blockcoord, 7> blocks = {{
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 2, 0 ) }},	// I-Tetrimino
	{{ std::make_pair( 0, 1 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},	// O-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 1 ) }},	// S-Tetrimino
	{{ std::make_pair(-1, 1 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }},	// Z-Tetrimino
	{{ std::make_pair(-1, 1 ), std::make_pair( 0, 0 ), std::make_pair(-1, 0 ), std::make_pair( 1, 0 ) }},	// L-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},	// J-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }}	// T-Tetrimino
}};

auto drawSingleBlock(sf::RenderWindow& wnd, sf::Color color, sf::Color border, float x, float y) -> void;

#endif