#include "grid.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

std::vector<GameSquare> create_grid(int screen_w, int screen_h, int square_length, std::vector<Entity> entities)
{
    if (screen_w < 0 || screen_h < 0 || square_length < 0)
    {
        throw std::runtime_error("Negative values are not allowed!");
    }

    if (screen_w % square_length != 0 || screen_h % square_length != 0)
    {
        throw std::runtime_error("Screen width and height must be divisible by square length!");
    }

    std::vector<GameSquare> squares;

    for (int i = 0; i < screen_w; i += square_length)
    {
        for (int j = 0; j < screen_h; j += square_length)
        {
            sf::RectangleShape outer_square(sf::Vector2f(square_length, square_length));
            sf::RectangleShape inner_square = sf::RectangleShape(sf::Vector2f(square_length - 2, square_length - 2));

            std::optional<sf::RectangleShape> entity_square = std::nullopt;

            outer_square.setPosition(i, j);
            outer_square.setFillColor(sf::Color(50, 50, 50));

            inner_square.setPosition(i + 1, j + 1);
            inner_square.setFillColor(sf::Color::Black);

            for (auto& entity : entities) {
                if (entity.position.x == i / square_length && entity.position.y == j / square_length) {
                    entity_square = sf::RectangleShape(sf::Vector2f(entity.entity_size, entity.entity_size));
                    int entity_offset = (square_length - entity.entity_size) / 2;
                    entity_square->setPosition(i + entity_offset, j + entity_offset);
                    entity_square->setFillColor(entity.entity_color);
                }
            }

            GameSquare gameSquare = { outer_square, inner_square, entity_square};
            squares.push_back(gameSquare);
        }
    }

    return squares;
}

void draw_grid(sf::RenderWindow& window, std::vector<GameSquare>& squares)
{
    for (auto& square : squares)
    {
        window.draw(square.outer_square);
        window.draw(square.inner_square);
        if (square.entity_square.has_value()) {
            auto entity_square = square.entity_square.value();
            window.draw(entity_square);
        }
    }
}

