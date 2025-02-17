#include <SFML/Graphics.hpp>
#include "entity.h"
#include <iostream>

Entity::Entity(int grid_size, sf::Vector2f position, sf::Sprite sprite)
{
    auto bounds = sprite.getGlobalBounds();
    this->size = bounds.getSize();
    sprite.setPosition(position);
    
    this->sprite = sprite;
    this->grid_size = grid_size;
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(this->sprite);
}

void Entity::setPosition(sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

sf::Vector2f Entity::getPosition()
{
    return this->sprite.getPosition();
}

void Entity::move(sf::Vector2f direction)
{
    direction = sf::Vector2f(direction.x * this->grid_size, direction.y * this->grid_size);
    auto position = this->getPosition();
    this->sprite.setPosition(position + direction);
}


sf::FloatRect Entity::getGlobalBounds()
{
    return this->sprite.getGlobalBounds();
}

void Entity::centerInSquare(sf::Vector2f square_position)
{
    auto bounds = this->getGlobalBounds();
    auto position = square_position;
    position.x =  position.x * this->grid_size + (this->grid_size - bounds.width) / 2;
    position.y = position.y * this->grid_size + (this->grid_size - bounds.height) / 2;
    this->setPosition(position);
}

sf::Vector2f Entity::getSquaredPosition()
{
    auto position = this->getPosition();
    position.x = int(position.x / this->grid_size);
    position.y = int(position.y / this->grid_size);
    return position;
}

bool Entity::wouldBeOutOfBounds(sf::Vector2f direction, sf::Vector2f grid_size)
{
    if (direction == sf::Vector2f(0,0))
    {
        return false;
    }

    auto playerBounds = this->sprite.getGlobalBounds();
    auto playerPos = this->getPosition();
    direction.x *= this->grid_size;
    direction.y *= this->grid_size;
    auto newPos = playerPos + direction;
    sf::FloatRect newBounds(newPos, playerBounds.getSize());

    return newPos.x < 0 || newPos.x + playerBounds.width > grid_size.x || newPos.y < 0 || newPos.y + playerBounds.height > grid_size.y;
}