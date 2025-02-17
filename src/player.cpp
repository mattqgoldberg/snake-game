#include "player.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(Entity entity) {
    this->entities.push_back(entity);
    this->score = 0;
}

void Player::increment_score() {
    this->score++;
}

int Player::get_score() {
    return this->score;
}

void Player::draw(sf::RenderWindow& window) {
    for (auto& entity : this->entities) {
        entity.draw(window);
    }
}

void Player::move(sf::Vector2f direction) {

    if (direction == sf::Vector2f(0, 0)) return;

    if (this->entities.size() == 1) {
        this->entities.front().move(direction);
        return;
    }

    if (this->entities.empty()) return;

    auto it = this->entities.begin();
    sf::Vector2f prev_pos = it->getPosition();;
    it->move(direction);
    it++;

    do {
        sf::Vector2f temp = it->getPosition();
        it->setPosition(prev_pos);
        prev_pos = temp;
        it++;
    }
    while (it != this->entities.end());
}

void Player::printPositions() {
    for (auto& entity : this->entities) {
        std::cout << "Position: " << entity.getPosition().x << ", " << entity.getPosition().y << std::endl;
    }
}

Entity Player::getHead() {
    return this->entities.front();
}

Entity Player::getTail() {
    return this->entities.back();
}

void Player::addEntity(Entity entity) {
    this->entities.push_back(entity);
}

std::list<Entity> Player::getEntities() {
    return this->entities;
}