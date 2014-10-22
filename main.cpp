#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "Block.hpp"
#include "Helpers.hpp"

std::array<std::array<int, bdWidth>, bdHeight> board{{}};

auto placeBlock(blockcoord bl, int x, int y) -> void;
auto drawBackground(sf::RenderWindow& wnd) -> void;

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
	unsigned int step;

public:
	Game()
	{
		step = 0;
		window.setFramerateLimit(60);
		aileronBlack.loadFromFile("./Aileron-Black.otf");

		text.setFont(aileronBlack);
		text.setPosition(10, 10);
		text.setCharacterSize(35.f);
		text.setColor(sf::Color::White);
		text.setString("Tetris");

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
		Block block;
		for (;;++step)
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
				if (step % 10 == 0) {
					block.move(0, 1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
				{
					if (step % 5 == 0)
					{
						// rotateBlock(block);
						block.rotate();
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
				{
					if (step % 5 == 0)
					{
						block.move(0, 1);
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
				{
					if (step % 5 == 0)
					{
						block.move(-1, 0);
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
				{
					if (step % 5 == 0)
					{
						block.move(1, 0);
					}
				}
				drawBackground(window);
				block.draw(window);
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
				drawSingleBlock(wnd, sf::Color::Black, sf::Color::Black, x, y);
			}
			else if (x == 0 || x == bdWidth+1 || y == 0 || y == bdHeight+1)
			{

				drawSingleBlock(wnd, gray, sf::Color::Black, x, y);
			}
			else
			{
				drawSingleBlock(wnd, sf::Color::White, gray, x, y);
			}
		}
	}
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
