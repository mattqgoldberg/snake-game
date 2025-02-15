#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(int grid_size, sf::Vector2f position, sf::Color color, int size);
    void move(sf::Vector2f direction);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    int grid_size;
    int size;
};

#endif // ENTITY_H