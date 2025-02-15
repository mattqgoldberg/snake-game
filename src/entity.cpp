#include <SFML/Graphics.hpp>
#include "entity.h"
#include <iostream>

Entity::Entity(int grid_size, sf::Vector2f position, sf::Color color, int size)
{
    shape = sf::RectangleShape(sf::Vector2f(size, size));
    this->position = sf::Vector2f(position.x * grid_size + (grid_size - size) / 2,
                                    position.y * grid_size + (grid_size - size) / 2);
    this->shape.setPosition(this->position);
    this->shape.setFillColor(color);
    this->grid_size = grid_size;
    this->size = size;
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Entity::move(sf::Vector2f direction)
{
    std::cout << "Current position: " << this->position.x << ", " << this->position.y << std::endl;
    std::cout << "Current shape position: " << this->shape.getPosition().x << ", " << this->shape.getPosition().y << std::endl;
    this->position.x += direction.x * this->grid_size;
    this->position.y += direction.y * this->grid_size;
    std::cout << "Moving to: " << this->position.x << ", " << this->position.y << std::endl;
    this->shape.setPosition(position);
    std::cout << "Shape position: " << this->shape.getPosition().x << ", " << this->shape.getPosition().y << std::endl;
}
