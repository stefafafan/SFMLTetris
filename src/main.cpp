#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include "Block.hpp"
#include "Helpers.hpp"

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
		std::unique_ptr<Block> block(new Block());
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
				auto blockMoving = false;
				auto moved = false;
				if (step % 10 == 0) 
				{
					moved = true;
					blockMoving = block->move(0, 1);					
					step = 0;
				}
				if (blockMoving)
				{
					if (step % 5 == 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
						{
								block->rotate();
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
						{
								block->move(0, 1);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
						{
								block->move(-1, 0);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
						{
								block->move(1, 0);
						}
					}
				}
				else if (moved)
				{
					block->placeBoard();
					block.reset(new Block());
				}
				drawBackground(window);
				block->draw(window);
			}
			window.display();
		}
	}
};

auto main() -> int
{
	Game game;
	game.run();
	return 0;
}
