#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"
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
        std::list<Entity> getEntities();
        std::list<Entity> getBabies();
        void reset();
        void setHighScore();
        int getHighScore();
    private:
        std::list<Entity> entities;
        int score;
        int high_score;
};