#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

constexpr unsigned int wndWidth{800}, wndHeight{450};
constexpr unsigned int bdWidth{10}, bdHeight{20};
std::array<std::array<int, bdHeight>, bdWidth> board;

class Manager
{
private:

public:

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
	sf::RenderWindow window{{wndWidth, wndHeight}, "Tetris?"};
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
				text.setString("Tetris with SFML & C++11/14\nBy Stefan Alexander");
				window.draw(text);
			}
			else if (state == State::GameOver)
			{
				text.setString("GameOver");
				window.draw(text);
			}
			else
			{
				text.setString("InGame");
				window.draw(text);
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
