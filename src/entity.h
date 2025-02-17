#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

class Entity {
public:
    Entity();
    Entity(int grid_size, sf::Vector2f position, sf::Color color, sf::Vector2f size);
    Entity(int grid_size, sf::Vector2f position, sf::Sprite sprite);
    void move(sf::Vector2f direction);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

private:
    std::variant<sf::RectangleShape, sf::Sprite> shape;
    int grid_size;
    sf::Vector2f size;
};
