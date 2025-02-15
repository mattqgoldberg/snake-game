#include <SFML/Window.hpp>
#include "entity.h"
#include "input.h"
#include <iostream>
#include <SFML/Graphics.hpp>


sf::Vector2f handleInput(sf::Vector2f direction) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        return sf::Vector2f(-1, 0);
    }   
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        return sf::Vector2f(1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        return sf::Vector2f(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        return sf::Vector2f(0, 1);
    }
    return direction;
}