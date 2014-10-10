#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>

auto checkEvent(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	window.clear();
	window.display();
}

auto main() -> int
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close);

	// Glew test.
	// glewExperimental = GL_TRUE;
	// glewInit();
	// GLuint vertexBuffer;
	// glGenBuffers(1, &vertexBuffer);
	// std::cout << "vertexBuffer: " << vertexBuffer << std::endl;

	while (window.isOpen())
	{
		checkEvent(window);
	}
	return 0;
}
