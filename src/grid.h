#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

std::vector<sf::RectangleShape> create_grid(int screen_w, int screen_h, int square_length);

void draw_grid(sf::RenderWindow& window, std::vector<sf::RectangleShape>& squares);

void update_grid(std::vector<sf::RectangleShape>& squares);