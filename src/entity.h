#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

class Entity {
public:
    Entity(int grid_size, sf::Vector2f position, sf::Sprite sprite);
    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f direction);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void centerInSquare(sf::Vector2f square_position);
    sf::Vector2f getSquaredPosition();
    bool wouldBeOutOfBounds(sf::Vector2f direction, sf::Vector2f grid_size);
private:
    sf::Sprite sprite;
    int grid_size;
    sf::Vector2f size;
};
