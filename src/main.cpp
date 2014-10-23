#include <iostream>
#include <memory>
#include <random>
#include <deque>
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
	sf::Text nextText;
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

		nextText = text;
		nextText.setPosition((2*constants::wndWidth/3)+10, 10);

		setupBackground();
	}
	auto run()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 6);
		std::deque<int> nextblocks { dis(gen), dis(gen),dis(gen) };
		std::unique_ptr<Block> block(new Block(dis(gen)));
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
			else
			{
				nextText.setString("Next:");
				window.draw(nextText);
				if (state == State::GameOver)
				{
					text.setString("GameOver");
					window.draw(text);
				}
				else
				{
					if (step % 4 == 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
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
					if (step % 7 == 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
						{
							block->rotate();
						}
					}
					auto blockMoving = false;
					auto moved = false;
					if (step % 10 == 0) 
					{
						moved = true;
						blockMoving = block->move(0, 1);
					}
					if (moved && !blockMoving)
					{
						block->placeBoard();
						checkLines();
						if (block->isOverflow())
						{
							state = State::GameOver;
						}
						else
						{
							block.reset(new Block(nextblocks.front()));
							nextblocks.pop_front();
							nextblocks.emplace_back(dis(gen));
							step = 0;
						}
					}
				}
				drawBackground(window);
				auto offset = 4;
				for (unsigned int i = 0; i < nextblocks.size(); ++i)
				{
					Block next(nextblocks.at(i));
					next.placeScreen(15, offset);
					next.draw(window);
					offset += 4;
				}
				
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
