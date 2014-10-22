#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "Block.hpp"
#include "Helpers.hpp"

std::array<std::array<int, constants::bdWidth+2>, constants::bdHeight+2> board{{}};

auto drawBackground(sf::RenderWindow& wnd) -> void;
auto setupBackground() -> void;

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
	sf::RenderWindow window{{constants::wndWidth, constants::wndHeight}, "SFML Tetris"};
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

		setupBackground();

		std::cout << "Board: " << std::endl;

		for (unsigned int i = 0; i < constants::bdHeight+2; ++i)
		{
			for (unsigned int j = 0; j < constants::bdWidth+2; ++j)
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

auto setupBackground() -> void
{
	auto midx = floor(constants::bdWidth/2);

	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(i).size(); ++j)
		{
			if (i == 0 && (midx - 2 <= j && j <= midx + 3))
			{
				board.at(i).at(j) = 9;	// Opening at top.
			}
			else if (j == 0 || j == constants::bdWidth+1 || i == 0 || i == constants::bdHeight+1)
			{

				board.at(i).at(j) = 8;	// Wall.
			}
			else
			{
				board.at(i).at(j) = 7;	// Nothing.
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

auto main() -> int
{
	Game game;
	game.run();
	return 0;
}
