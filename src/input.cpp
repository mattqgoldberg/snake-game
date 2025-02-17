#include <SFML/Window.hpp>
#include "entity.h"
#include "input.h"
#include <iostream>
#include <SFML/Graphics.hpp>


sf::Vector2f handleInput(sf::Vector2f direction) {
    sf::Vector2f new_direction = direction;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        new_direction = sf::Vector2f(-1, 0);
    }   
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        new_direction = sf::Vector2f(1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        new_direction = sf::Vector2f(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        new_direction = sf::Vector2f(0, 1);
    }

    if (new_direction == -direction)
    {
        return direction;
    }
    return new_direction;
}