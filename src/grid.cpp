#include "grid.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <iostream>

Grid::Grid(int screen_w, int screen_h, int square_length)
{
    if (screen_w < 0 || screen_h < 0 || square_length < 0)
    {
        throw std::runtime_error("Negative values are not allowed!");
    }

    if (screen_w % square_length != 0 || screen_h % square_length != 0)
    {
        throw std::runtime_error("Screen width and height must be divisible by square length!");
    }

    screen_w = screen_w;
    screen_h = screen_h;
    square_length = square_length;

    for (int j = 0; j < screen_h; j += square_length)
    {
        for (int i = 0; i < screen_w; i += square_length)
        {
            sf::RectangleShape outer_square(sf::Vector2f(square_length, square_length));
            sf::RectangleShape inner_square = sf::RectangleShape(sf::Vector2f(square_length - 2, square_length - 2));

            outer_square.setPosition(i, j);
            outer_square.setFillColor(sf::Color(50, 50, 50));

            inner_square.setPosition(i + 1, j + 1);
            inner_square.setFillColor(sf::Color::Black);

            GameSquare gameSquare = { outer_square, inner_square };
            squares.push_back(gameSquare);
        }
    }
}

void Grid::draw(sf::RenderWindow& window)
{
    for (auto& square : squares)
    {
        window.draw(square.outer_square);
        window.draw(square.inner_square);
    }
}
