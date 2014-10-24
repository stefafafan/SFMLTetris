#include <iostream>
#include <memory>
#include <random>
#include <deque>
#include <string>
#include "Block.hpp"
#include "Helpers.hpp"

class Game
{
private:
	enum class State 
	{
		InGame,
		GameOver
	};
	State state{State::InGame};
	sf::RenderWindow window{{constants::wndWidth, constants::wndHeight}, "SFML Tetris"};
	sf::Font aileronBlack;
	sf::Text text;
	sf::Text nextText;
	sf::Text holdText;
	sf::Text linesText;
	unsigned int step;
	unsigned int linecount;

public:
	Game()
	{
		step = 0;
		linecount = 0;
		window.setFramerateLimit(60);
		aileronBlack.loadFromFile("./Aileron-Black.otf");

		text.setFont(aileronBlack);
		text.setPosition(10, 10);
		text.setCharacterSize(35.f);
		text.setColor(sf::Color::White);
		text.setString("Tetris");

		nextText = text;
		nextText.setPosition((2*constants::wndWidth/3)+30, 10);

		holdText = text;
		holdText.setPosition((constants::wndWidth/7), constants::wndHeight/4);

		linesText = text;
		linesText.setPosition((constants::wndWidth/7), constants::wndHeight/2);

		setupBackground();
	}
	auto run() -> void
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 6);
		std::deque<int> nextblocks { dis(gen), dis(gen),dis(gen) };
		std::unique_ptr<Block> block(new Block(dis(gen)));
		auto holdtype = -1;
		auto canSwap = true;
		sf::Event event;
		for (;;++step)
		{
			window.pollEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			window.clear(sf::Color::Black);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) 
			{
				setupBackground();
				nextblocks.clear();
				nextblocks = { dis(gen), dis(gen),dis(gen) };
				block.reset(new Block(dis(gen)));
				holdtype = -1;
				canSwap = true;
				linecount = 0;
				state = State::InGame;
			}


			nextText.setString("Next:");
			window.draw(nextText);
			holdText.setString("Hold:");
			window.draw(holdText);
			std::string line = "Lines:\n" + std::to_string(linecount);
			linesText.setString(line);
			window.draw(linesText);
			if (state == State::GameOver)
			{
				text.setString("GameOver");
				window.draw(text);
			}
			else
			{
				if (step % 4 == 0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !block->startedFalling())
					{
						block->drop();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
					{
						block->move(0, 1);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
					{
						block->move(-1, 0);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
					{
						block->move(1, 0);
					}
				}
				if (step % 7 == 0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) 
					{
						block->rotate(true);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
					{
						block->rotate(false);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
					{
						if (holdtype == -1)
						{
							holdtype = block->getType();
							block.reset(new Block(nextblocks.front()));
							nextblocks.pop_front();
							nextblocks.emplace_back(dis(gen));
						}
						else if (canSwap)
						{
							auto temp = block->getType();
							block.reset(new Block(holdtype));
							holdtype = temp;
							canSwap = false;
						}
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
					linecount += checkLines();
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
						canSwap = true;
					}
				}
			}
			drawBackground(window);

				// Draw next blocks.
			auto offset = 4;
			for (unsigned int i = 0; i < nextblocks.size(); ++i)
			{
				Block next(nextblocks.at(i));
				next.placeScreen(15, offset);
				next.draw(window);
				offset += 4;
			}

				// Draw hold block.
			if (holdtype != -1)
			{
				Block hold(holdtype);
				hold.placeScreen(-6, 8);
				hold.setGhost(!canSwap);
				hold.draw(window);
			}

				// Draw current block.
			block->draw(window);

				// Create and draw ghost block.
			Block ghost = *block;
			ghost.setGhost(true);
			ghost.drop();
			ghost.draw(window);
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
