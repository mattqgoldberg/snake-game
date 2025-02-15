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
    
    Grid grid(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }
}
