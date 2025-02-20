#include "setup.hpp"

void setUpSprite(sf::Sprite& sprite, sf::Texture& texture, const int GRID_SIZE, float x_grid_percent, float y_grid_percent) {
    sprite.setTexture(texture);
    auto bounds = sprite.getGlobalBounds();
    float scaleX = (GRID_SIZE * x_grid_percent) / bounds.width;
    float scaleY = (GRID_SIZE * y_grid_percent) / bounds.height;
    sprite.setScale(scaleX, scaleY);
}

void randomizeMatt(Entity& matt, Entity& player, const int GRID_WIDTH, const int GRID_HEIGHT, const int GRID_SIZE)
{
    sf::Vector2f mattSquare(0,0);
    do {
        int x_max = GRID_WIDTH / GRID_SIZE - 1;
        int y_max = GRID_HEIGHT / GRID_SIZE - 1;
        int rand_x = std::rand() % (x_max + 1);
        int rand_y = std::rand() % (y_max + 1);
        auto size = matt.getGlobalBounds().getSize();
        mattSquare = sf::Vector2f(rand_x,rand_y);
        matt.centerInSquare(mattSquare);
    } while (mattSquare == player.getSquaredPosition());
}

void setUpText(sf::Text& text, sf::Font& font, const std::string& str, int size, sf::Color color, sf::Vector2f position)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}