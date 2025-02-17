#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <optional>

struct GameSquare {
    sf::RectangleShape outer_square;
    sf::RectangleShape inner_square;
};

class Grid {
    public:
        Grid(int screen_w, int screen_h, int square_length);
        void draw(sf::RenderWindow& window);
    private:
        std::vector<GameSquare> squares;
        int screen_w;
        int screen_h;
        int square_length;
};
