#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <optional>

struct GameSquare {
    sf::RectangleShape outer_square;
    sf::RectangleShape inner_square;
    std::optional<sf::RectangleShape> entity_square;
};

struct Entity {
    sf::Color entity_color;
    sf::Vector2f position;
    int entity_size;
};

std::vector<GameSquare> create_grid(int screen_w, int screen_h, int square_length, std::vector<Entity> entities);

void draw_grid(sf::RenderWindow& window, std::vector<GameSquare>& squares);