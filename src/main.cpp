#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "grid.h"
#include "entity.h"
#include "input.h"
#include "player.h"
#include <filesystem>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
int GRID_WIDTH = 800;
int GRID_HEIGHT = 700;
int GRID_SIZE = 100;
bool game_over = false;

bool detectCollision(Entity player, Entity fruit)
{
    auto playerBounds = player.getGlobalBounds();
    auto fruitBounds = fruit.getGlobalBounds();

    return playerBounds.intersects(fruitBounds);
}

bool wouldCollide(Entity player, Entity fruit, sf::Vector2f direction)
{
    if (direction == sf::Vector2f(0,0))
    {
        return false;
    }

    auto playerBounds = player.getGlobalBounds();
    auto fruitBounds = fruit.getGlobalBounds();

    auto playerPos = player.getPosition();
    std::cout << "Player position: " << playerPos.x << ", " << playerPos.y << std::endl;
    auto fruitPos = fruit.getPosition();

    
    direction.x *= GRID_SIZE;
    direction.y *= GRID_SIZE;
    auto newPos = playerPos + direction;

    std::cout << "New position: " << newPos.x << ", " << newPos.y << std::endl;
    std::cout << "Fruit position: " << fruitPos.x << ", " << fruitPos.y << std::endl;
    sf::FloatRect newBounds(newPos, playerBounds.getSize());

    return newBounds.intersects(fruitBounds);
}

bool wouldCollide(Entity player, std::list<Entity> entities, sf::Vector2f direction)
{
    if (direction == sf::Vector2f(0,0))
    {
        return false;
    }

    auto playerBounds = player.getGlobalBounds();
    auto playerPos = player.getPosition();
    direction.x *= GRID_SIZE;
    direction.y *= GRID_SIZE;
    auto newPos = playerPos + direction;
    sf::FloatRect newBounds(newPos, playerBounds.getSize());

    for (auto& entity : entities)
    {
        auto entityBounds = entity.getGlobalBounds();
        if (newBounds.intersects(entityBounds))
        {
            return true;
        }
    }

    return false;
}

bool wouldBeOutOfBounds(Entity player, sf::Vector2f direction)
{
    if (direction == sf::Vector2f(0,0))
    {
        return false;
    }

    auto playerBounds = player.getGlobalBounds();
    auto playerPos = player.getPosition();
    direction.x *= GRID_SIZE;
    direction.y *= GRID_SIZE;
    auto newPos = playerPos + direction;
    sf::FloatRect newBounds(newPos, playerBounds.getSize());

    return newPos.x < 0 || newPos.x + playerBounds.width > GRID_WIDTH || newPos.y < 0 || newPos.y + playerBounds.height > GRID_HEIGHT;
}


void randomizeMatt(Entity& matt)
{
    int x_max = GRID_WIDTH / GRID_SIZE - 1;
    int y_max = GRID_HEIGHT / GRID_SIZE - 1;
    int rand_x = std::rand() % (x_max + 1);
    int rand_y = std::rand() % (y_max + 1);
    auto size = matt.getGlobalBounds().getSize();
    sf::Vector2f playerPos(0,0);
    playerPos.x =  rand_x * GRID_SIZE + (GRID_SIZE - size.x) / 2;
    playerPos.y = rand_y * GRID_SIZE - size.y + GRID_SIZE - 1;
    matt.setPosition(playerPos);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application");
    
    Grid grid(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);

    
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

    sf::Vector2f mattPos(0,0);
    mattPos.x =  5 * GRID_SIZE + (GRID_SIZE - bounds.width) / 2;
    mattPos.y = 5 * GRID_SIZE - bounds.height + GRID_SIZE - 1;
    Entity matt(GRID_SIZE, mattPos, mattSprite);
    

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    bounds = playerSprite.getGlobalBounds();
    scaleX = (GRID_SIZE * 0.67) / bounds.width;
    scaleY = (GRID_SIZE * 0.87) / bounds.height;
    playerSprite.setScale(scaleX, scaleY);


    sf::Sprite miniSprite;
    miniSprite.setTexture(playerTexture);
    scaleX = (GRID_SIZE * 0.37) / bounds.width;
    scaleY = (GRID_SIZE * 0.37) / bounds.height;
    miniSprite.setScale(scaleX, scaleY);

    sf::Vector2f playerPos(3,3);
    auto size = playerSprite.getGlobalBounds().getSize();
    playerPos.x =  playerPos.x * GRID_SIZE + (GRID_SIZE - size.x) / 2;
    playerPos.y = playerPos.y * GRID_SIZE - size.y + GRID_SIZE - 1;
    Entity playerEntity(GRID_SIZE, playerPos, playerSprite);

    Player player(playerEntity);

    
    sf::Font font;
    font.loadFromFile("TimesNewRoman.otf");
    sf:: Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 710);
    scoreText.setString("Score: 0");

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(300, 300);
    gameOverText.setString("Game Over!");


    sf::SoundBuffer baby_buffer;
    if (!baby_buffer.loadFromFile("baby1.mp3"))
        return -1;

    sf::Sound baby_sound;
    baby_sound.setBuffer(baby_buffer);
    
    sf::SoundBuffer no_buffer;
    if (!no_buffer.loadFromFile("no1.mp3"))
        return -1;

    sf::Sound no_sound;
    no_sound.setBuffer(no_buffer);


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

             


            if (direction != sf::Vector2f(0,0) && !game_over)
            {

                if (wouldCollide(player.getHead(), player.getEntities(), direction))
                {
                    game_over = true;
                    baby_sound.stop();
                    no_sound.play();
                }

                if (wouldBeOutOfBounds(player.getHead(), direction))
                {
                    game_over = true;
                    baby_sound.stop();
                    no_sound.play();
                }

                if (wouldCollide(player.getHead(), matt, direction))
                {
                    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    randomizeMatt(matt);
                    
                    player.increment_score();
                    Entity newPlayerEntity = Entity(GRID_SIZE, player.getTail().getPosition(), miniSprite);
                    player.move(direction);

                    player.addEntity(newPlayerEntity);
                    player.increment_score();
                    baby_sound.play();
                    std::string str_score = "Score: " + std::to_string(player.get_score());
                    scoreText.setString(str_score);
                    
                }
                else {
                    player.move(direction);
                }
            }
            clock.restart();
        }
        
        window.clear();
        if (!game_over)
        {
            grid.draw(window);
            matt.draw(window);
            player.draw(window);
            window.draw(scoreText);
        }

        else {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(48);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(300, 300);
            gameOverText.setString("Game Over!");
            window.draw(gameOverText);
        }
        
        window.display();
    }
}
