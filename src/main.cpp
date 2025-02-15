#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "grid.h"
#include "entity.h"
#include "input.h"

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;
int GRID_SIZE = 20;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    
    Grid grid(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);

    Entity player(GRID_SIZE, sf::Vector2f(10, 10), sf::Color::Green, 6);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        handleInput(player);

        window.clear();
        grid.draw(window);
        player.draw(window);
        window.display();
    }
}
