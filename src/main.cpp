#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "grid.h"
#include "entity.h"
#include "input.h"
#include "player.h"
#include <filesystem>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
int GRID_WIDTH = 800;
int GRID_HEIGHT = 700;
int GRID_SIZE = 100;

bool detectCollision(Entity player, Entity fruit)
{
    auto playerBounds = player.getGlobalBounds();
    auto fruitBounds = fruit.getGlobalBounds();

    return playerBounds.intersects(fruitBounds);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application");
    
    Grid grid(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);

    sf::Vector2f playerPos(1,1);
    sf::Texture playerTexture;

    std::cout << "Current working directory: " 
    << std::filesystem::current_path() << std::endl;

    if (!playerTexture.loadFromFile("avatar.png")) {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }

    sf::Texture mattTexture;
    if (!mattTexture.loadFromFile("matt.png")) {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }

    sf::Sprite mattSprite;
    mattSprite.setTexture(mattTexture);
    auto bounds = mattSprite.getGlobalBounds();
    float scaleX = (GRID_SIZE * 0.7) / bounds.width;
    float scaleY = (GRID_SIZE * 0.9) / bounds.height;
    mattSprite.setScale(scaleX, scaleY);

    Entity matt(GRID_SIZE, sf::Vector2f(5, 5), mattSprite);


    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    bounds = playerSprite.getGlobalBounds();
    scaleX = (GRID_SIZE * 0.67) / bounds.width;
    scaleY = (GRID_SIZE * 0.87) / bounds.height;
    playerSprite.setScale(scaleX, scaleY);

    Entity playerEntity(GRID_SIZE, playerPos, playerSprite);

    Player player(playerEntity);

    


    sf::Clock clock;

    sf::Vector2f direction(0, 0);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        direction = handleInput(direction);

        if (clock.getElapsedTime().asMilliseconds() > 200)
        {
            player.move(direction);
            clock.restart();
        }
        
        bool collided = detectCollision(player.getEntity(), matt);
        if (collided)
        {
            player.increment_score();
            int x_max = GRID_WIDTH / GRID_SIZE - 1;
            int y_max = GRID_HEIGHT / GRID_SIZE - 1;
            int rand_x = std::rand() % (x_max + 1);
            int rand_y = std::rand() % (y_max + 1);
            std::cout << "Random x: " << rand_x << " Random y: " << rand_y << std::endl;
            matt = Entity(GRID_SIZE, sf::Vector2f(rand_x, rand_y), mattSprite);
        }


        window.clear();
        grid.draw(window);
        player.draw(window);
        matt.draw(window);
        window.display();
    }
}
