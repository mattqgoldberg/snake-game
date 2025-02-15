#include <SFML/Graphics.hpp>
#include "entity.h"

Entity::Entity(int grid_size, sf::Vector2f position, sf::Color color, int size)
{
    shape = sf::RectangleShape(sf::Vector2f(size, size));
    position.x = position.x * grid_size + (grid_size - size) / 2;
    position.y = position.y * grid_size + (grid_size - size) / 2;
    shape.setPosition(position);
    shape.setFillColor(color);
    grid_size = grid_size;
    size = size;
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Entity::move(sf::Vector2f direction)
{
    position += sf::Vector2f(direction.x * grid_size, direction.y * grid_size);
    shape.setPosition(position);
}
