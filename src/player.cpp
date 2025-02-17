#include "player.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

Player::Player(Entity entity) : entity(entity) {
    this->entity = entity;
    this->score = 0;
}

void Player::increment_score() {
    this->score++;
}

int Player::get_score() {
    return this->score;
}

void Player::draw(sf::RenderWindow& window) {
    this->entity.draw(window);
}

void Player::move(sf::Vector2f direction) {
    this->entity.move(direction);
}

Entity Player::getEntity() {
    return this->entity;
}