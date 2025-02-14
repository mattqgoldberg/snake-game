#include "grid.h"
#include <SFML/Graphics.hpp>
#include <vector>

std::vector<sf::RectangleShape> create_grid(int screen_w, int screen_h, int square_length)
{
    if (screen_w < 0 || screen_h < 0 || square_length < 0)
    {
        throw std::runtime_error("Negative values are not allowed!");
    }

    if (screen_w % square_length != 0 || screen_h % square_length != 0)
    {
        throw std::runtime_error("Screen width and height must be divisible by square length!");
    }


    std::vector<sf::RectangleShape> squares;

    for (int i = 0; i < screen_w; i += square_length)
    {
        for (int j = 0; j < screen_h; j += square_length)
        {
            sf::RectangleShape square(sf::Vector2f(square_length, square_length));
            square.setPosition(i, j);
            if (i % (2 * square_length) == 0 && j % (2 * square_length) == 0) {
                square.setFillColor(sf::Color::White);
            }
            else if (i % (2 * square_length) != 0 && j % (2 * square_length) != 0) {
                square.setFillColor(sf::Color::Blue);
            }
            else {
                square.setFillColor(sf::Color::Green);
            }
            squares.push_back(square);
        }
    }

    return squares;
}

void draw_grid(sf::RenderWindow& window, std::vector<sf::RectangleShape>& squares)
{
    for (auto& square : squares)
    {
        window.draw(square);
    }
}

void update_grid(std::vector<sf::RectangleShape>& squares)
{
    for (auto& square : squares)
    {
        if (square.getFillColor() == sf::Color::White)
        {
            square.setFillColor(sf::Color::Green);
        }
        else if (square.getFillColor() == sf::Color::Green)
        {
            square.setFillColor(sf::Color::Blue);
        }
        else
        {
            square.setFillColor(sf::Color::White);
        }
    }
}

