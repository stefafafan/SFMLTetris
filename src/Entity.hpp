#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual ~Entity() { }
    virtual auto draw(sf::RenderWindow&) -> void { }
};

#endif
