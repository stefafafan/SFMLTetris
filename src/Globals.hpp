#ifndef GLOBALS_HPP
#define GLOBALS_HPP

using blockcoord = std::array<std::pair<int, int>, 4>;

namespace constants
{
	constexpr int wndWidth{1280}, wndHeight{720};
	constexpr int bdWidth{10}, bdHeight{20};

	constexpr std::array<blockcoord, 7> blocks = {{
		{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 2, 0 ) }},   // I-Tetrimino
		{{ std::make_pair( 0, 1 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},   // O-Tetrimino
		{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 1 ) }},   // S-Tetrimino
		{{ std::make_pair(-1, 1 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }},   // Z-Tetrimino
		{{ std::make_pair(-1, 1 ), std::make_pair( 0, 0 ), std::make_pair(-1, 0 ), std::make_pair( 1, 0 ) }},   // L-Tetrimino
		{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},   // J-Tetrimino
		{{ std::make_pair(-1, 0 ), std::make_pair( 0, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }}    // T-Tetrimino
	}};

	const std::array<sf::Color, 10> blockcolors = {{
		sf::Color(255, 0, 0),       // 0. Red           I-Tetrimino
		sf::Color(255, 240, 0),     // 1. Yellow        O-Tetrimino
		sf::Color(200, 30, 140),    // 2. Purple        S-Tetrimino
		sf::Color(50, 200, 50),     // 3. Green         Z-Tetrimino
		sf::Color(255, 128, 0),     // 4. Orange        L-Tetrimino
		sf::Color(0, 0, 255),       // 5. Blue          J-Tetrimino
		sf::Color(0, 255, 255),     // 6. Light Blue    T-Tetrimino
		sf::Color(255, 255, 255),   // 7. White         Background
		sf::Color(128, 128, 128),   // 8. Gray          Wall
		sf::Color(0, 0, 0)          // 9. Black         Opening
	}};
}

#endif