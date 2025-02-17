#pragma once
#include "entity.h"
#include <list>

class Player {
    public:
        Player(Entity entity);
        void increment_score();
        int get_score();
        void draw(sf::RenderWindow& window);
        void move(sf::Vector2f direction);
        Entity getHead();
        Entity getTail();
        void addEntity(Entity entity);
        void printPositions();
        std::list<Entity> getEntities();
    private:
        std::list<Entity> entities;
        int score;
};