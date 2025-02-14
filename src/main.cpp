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
    
    std::vector<sf::RectangleShape> squares = create_grid(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);

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
        draw_grid(window, squares);
        if (clock.getElapsedTime().asSeconds() > 0.5)
        {
            update_grid(squares);
            clock.restart();
        }
        window.display();
    }
}
