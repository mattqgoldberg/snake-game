#include "player.hpp"

Player::Player(Entity entity) {
    this->entities.push_back(entity);
    this->score = 0;
    this->high_score = 0;
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
    sf::Vector2f prev_pos = it->getSquaredPosition();;
    it->move(direction);
    it++;

    do {
        auto temp = it->getSquaredPosition();
        it->centerInSquare(prev_pos);
        prev_pos = temp;
        it++;
    }
    while (it != this->entities.end());
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

std::list<Entity> Player::getBabies() {
    std::list<Entity> babies;
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (it != this->entities.begin()) {
            babies.push_back(*it);
        }
    }
    return babies;
}

void Player::reset() {
    auto head = this->entities.front();
    this->entities.clear();
    this->score = 0;




    head.centerInSquare(sf::Vector2f(3, 3));
    this->entities.push_back(head);
}

void Player::setHighScore() {
    if (this->score > this->high_score) {
        this->high_score = this->score;
    }
}

int Player::getHighScore() {
    return this->high_score;
}
