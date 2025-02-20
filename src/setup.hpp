#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>

void setUpSprite(sf::Sprite& sprite, sf::Texture& texture, int GRID_SIZE, float x_grid_percent, float y_grid_percent);
void randomizeMatt(Entity& matt, Entity& player, int GRID_WIDTH, int GRID_HEIGHT, int GRID_SIZE);
void setUpText(sf::Text& text, sf::Font& font, const std::string& str, int size, sf::Color color, sf::Vector2f position);