#include <SFML/Graphics.hpp>
#include "entity.h"
#include <iostream>

Entity::Entity()
{
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Green);
    this->shape = rect;
    this->grid_size = 50;
}

Entity::Entity(int grid_size, sf::Vector2f position, sf::Color color, sf::Vector2f size)
{
    sf::RectangleShape rect(size);
    this->size = size;

    position.x =  position.x * grid_size + (grid_size - this->size.x) / 2,
    position.y = position.y * grid_size + (grid_size - this->size.y) / 2;
    rect.setPosition(position);
    rect.setFillColor(color);
    this->shape = rect;
    this->grid_size = grid_size;
}

Entity::Entity(int grid_size, sf::Vector2f position, sf::Sprite sprite)
{
    auto bounds = sprite.getGlobalBounds();
    this->size = bounds.getSize();
    sprite.setPosition(position.x * grid_size + (grid_size - this->size.x) / 2,
    position.y * grid_size - this->size.y + grid_size - 1);
    
    this->shape = sprite;
    this->grid_size = grid_size;
}

void Entity::draw(sf::RenderWindow& window)
{
    std::visit([&window](auto& s) { window.draw(s); }, this->shape);
}

void Entity::move(sf::Vector2f direction)
{
    direction = sf::Vector2f(direction.x * this->grid_size, direction.y * this->grid_size);
    auto position = std::visit([](auto& s) { return s.getPosition(); }, this->shape);
    std::visit([direction, position](auto& s) { s.setPosition(position + direction); }, this->shape);
    //std::cout << "Position: " << std::visit([direction, position](auto& s) { return s.getPosition().x; }, this->shape) << std::endl;
}


sf::FloatRect Entity::getGlobalBounds()
{
    return std::visit([](auto& s) { return s.getGlobalBounds(); }, this->shape);
}