#pragma once
#include "entity.h"

class Player {
    public:
        Player(Entity entity);
        void increment_score();
        int get_score();
        void draw(sf::RenderWindow& window);
        void move(sf::Vector2f direction);
        Entity getEntity();
    private:
        Entity entity;
        int score;
};