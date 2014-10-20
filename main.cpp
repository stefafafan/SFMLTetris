#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <random>
#include <utility>
#include <cmath>

constexpr int wndWidth{800}, wndHeight{450};
constexpr int bdWidth{10}, bdHeight{20};
std::array<std::array<int, bdWidth>, bdHeight> board{{}};

using blockcoord = std::array<std::pair<int, int>, 3>;

constexpr std::array<blockcoord, 8> blocks = {{
	{{ std::make_pair( 0, 0 ), std::make_pair( 0, 0 ), std::make_pair( 0, 0 ) }},	// Null
	{{ std::make_pair(-1, 0 ), std::make_pair( 1, 0 ), std::make_pair( 2, 0 ) }},	// I-Tetrimino
	{{ std::make_pair( 0, 1 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},	// O-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 1 ) }},	// S-Tetrimino
	{{ std::make_pair(-1, 1 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }},	// Z-Tetrimino
	{{ std::make_pair(-1, 1 ), std::make_pair(-1, 0 ), std::make_pair( 1, 0 ) }},	// L-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 1, 0 ), std::make_pair( 1, 1 ) }},	// J-Tetrimino
	{{ std::make_pair(-1, 0 ), std::make_pair( 0, 1 ), std::make_pair( 1, 0 ) }}	// T-Tetrimino
}}; 

auto placeBlock(blockcoord bl, int x, int y) -> void;
auto drawBackground(sf::RenderWindow& wnd) -> void;
auto drawBlock(sf::RenderWindow& wnd, sf::Color color, sf::Color border, int x, int y) -> void;

class Block
{
private:
	unsigned int x;
	unsigned int y;
	unsigned int type;

public:
	blockcoord coordinates;
	Block():x(0), y(0)
	{
		std::cout << "New Block: (" << x << ", " << y << ")" << std::endl;
		generateBlock();
	}
	auto generateBlock() -> void
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 6);
		type = dis(gen);

		std::cout << "Block Type: " << type << std::endl;

		coordinates = blocks.at(type);

		std::cout << coordinates.at(0).first << " " << coordinates.at(0).second << std::endl;
		std::cout << coordinates.at(1).first << " " << coordinates.at(1).second << std::endl;
		std::cout << coordinates.at(2).first << " " << coordinates.at(2).second << std::endl;
	}
};

class Game
{
private:
	enum class State 
	{
		Title,
		InGame,
		GameOver
	};
	State state{State::Title};
	sf::RenderWindow window{{wndWidth, wndHeight}, "SFML Tetris"};
	sf::Font aileronBlack;
	sf::Text text;

public:
	Game()
	{
		window.setFramerateLimit(60);
		aileronBlack.loadFromFile("./Aileron-Black.otf");

		text.setFont(aileronBlack);
		text.setPosition(10, 10);
		text.setCharacterSize(35.f);
		text.setColor(sf::Color::White);
		text.setString("Tetris");

		Block block;
		placeBlock(block.coordinates, 1, bdWidth/2 - 1);

		std::cout << "Board: " << std::endl;

		for (unsigned int i = 0; i < bdHeight; ++i)
		{
			for (unsigned int j = 0; j < bdWidth; ++j)
			{
				std::cout << board.at(i).at(j) << " ";
			}
			std::cout << std::endl;
		}
		
	}
	auto run()
	{
		while (true)
		{
			window.clear(sf::Color::Black);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) 
			{
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
			{
				state = State::InGame;
			}

			if (state == State::Title)
			{
				text.setString("SFML Tetris\nStefan Alexander");
				window.draw(text);
			}
			else if (state == State::GameOver)
			{
				text.setString("GameOver");
				window.draw(text);
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
				{
					std::cout << "Up" << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
				{
					std::cout << "Down" << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
				{
					std::cout << "Left" << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
				{
					std::cout << "Right" << std::endl;
				}
				text.setString("InGame");
				drawBackground(window);
			}
			window.display();
		}
	}
};

auto drawBackground(sf::RenderWindow& wnd) -> void
{
	sf::Color gray(128, 128, 128);
	auto midx = floor(bdWidth/2);
	for (auto x = 0; x < bdWidth+2; ++x)
	{
		for (auto y = 0; y < bdHeight+2; ++y)
		{
			if (y == 0 && (x >= midx - 2 && x <= midx + 3))
			{
				drawBlock(wnd, sf::Color::Black, sf::Color::Black, x, y);
			}
			else if (x == 0 || x == bdWidth+1 || y == 0 || y == bdHeight+1)
			{

				drawBlock(wnd, gray, sf::Color::Black, x, y);
			}
			else
			{
				drawBlock(wnd, sf::Color::White, gray, x, y);
			}
		}
	}
}

auto drawBlock(sf::RenderWindow& wnd, sf::Color color, sf::Color border, int x, int y) -> void
{
	auto blockx = (wndWidth/3.f)/(bdWidth+2.f);
	auto blocky = wndHeight/(bdHeight+2.f);
	sf::RectangleShape shape;
	shape.setPosition((wndWidth/3.f)+(x*blockx)+(blockx/2.f), (y*blocky)+(blocky/2.f));
	shape.setSize({blockx, blocky});
	shape.setFillColor(color);
	shape.setOutlineColor(border);
	shape.setOutlineThickness(-1.f);
	shape.setOrigin(blockx/2.f, blocky/2.f);
	wnd.draw(shape);
}

auto placeBlock(blockcoord bl, int x, int y) -> void
{
	if (x >= 0 && y >= 0)
	{
		board.at(x).at(y) = 1;
	}
	for (auto coord : bl)
	{
		auto newx = x+coord.first;
		auto newy = y+coord.second;
		if (newx >= 0 && newy >= 0)
		{
			board.at(newx).at(newy) = 1;
		}
	}
}

auto main() -> int
{
	Game game;
	game.run();
	return 0;
}
