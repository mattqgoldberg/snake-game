#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "grid.h"

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;
int GRID_SIZE = 20;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    
    std::vector<Entity> entities = {
        {sf::Color::Red, sf::Vector2f(0, 0), 2},
        {sf::Color::Green, sf::Vector2f(10, 10), 4},
        {sf::Color::Blue, sf::Vector2f(5, 5), 8}
    };
    
    std::vector<GameSquare> grid = create_grid(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE, entities);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        draw_grid(window, grid);
        // if (clock.getElapsedTime().asSeconds() > 0.5)
        // {
        //     update_grid(squares);
        //     clock.restart();
        // }
        window.display();
    }
}
