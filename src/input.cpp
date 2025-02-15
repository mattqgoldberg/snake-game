#include <SFML/Window.hpp>
#include "entity.h"

void handleInput(Entity character) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        // left key is pressed: move our character
        character.move({-1.f, 0.f});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        // right key is pressed: move our character
        character.move({1.f, 0.f});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // up key is pressed: move our character
        character.move({0.f, -1.f});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        // down key is pressed: move our character
        character.move({0.f, 1.f});
    }
}