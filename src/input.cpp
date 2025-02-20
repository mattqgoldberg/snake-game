#include "input.hpp"

sf::Vector2f handleInput(sf::Vector2f movement_dir, sf::Vector2f current_dir) {

    sf::Vector2f new_dir = current_dir;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
       new_dir = sf::Vector2f(-1,0);
    }   
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        new_dir = sf::Vector2f(1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        new_dir = sf::Vector2f(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        new_dir = sf::Vector2f(0, 1);
    }

    if (movement_dir == -new_dir)
    {
        return current_dir;
    }
    return new_dir;
}