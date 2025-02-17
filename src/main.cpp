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

void randomizeMatt(Entity& matt, Entity player)
{
    sf::Vector2f mattSquare(0,0);
    do {
        int x_max = GRID_WIDTH / GRID_SIZE - 1;
        int y_max = GRID_HEIGHT / GRID_SIZE - 1;
        int rand_x = std::rand() % (x_max + 1);
        int rand_y = std::rand() % (y_max + 1);
        auto size = matt.getGlobalBounds().getSize();
        mattSquare = sf::Vector2f(rand_x,rand_y);
        matt.centerInSquare(mattSquare);
    } while (mattSquare == player.getSquaredPosition());
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    
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

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    auto bounds = playerSprite.getGlobalBounds();
    float scaleX = (GRID_SIZE * 0.67) / bounds.width;
    float scaleY = (GRID_SIZE * 0.87) / bounds.height;
    playerSprite.setScale(scaleX, scaleY);

    sf::Sprite miniSprite;
    miniSprite.setTexture(playerTexture);
    scaleX = (GRID_SIZE * 0.37) / bounds.width;
    scaleY = (GRID_SIZE * 0.37) / bounds.height;
    miniSprite.setScale(scaleX, scaleY);

    sf::Sprite miniMattSprite;
    miniMattSprite.setTexture(mattTexture);
    scaleX = (GRID_SIZE * 0.4) / bounds.width;
    scaleY = (GRID_SIZE * 0.4) / bounds.height;
    miniMattSprite.setScale(scaleX, scaleY);


    sf::Vector2f playerSquare(3,3);
    Entity playerEntity(GRID_SIZE, sf::Vector2f(0,0), playerSprite);
    playerEntity.centerInSquare(playerSquare);
    Player player(playerEntity);

    sf::Sprite mattSprite;
    mattSprite.setTexture(mattTexture);
    bounds = mattSprite.getGlobalBounds();
    scaleX = (GRID_SIZE * 0.7) / bounds.width;
    scaleY = (GRID_SIZE * 0.9) / bounds.height;
    mattSprite.setScale(scaleX, scaleY);

    sf::Vector2f mattPos(0,0);
    Entity matt(GRID_SIZE, mattPos, mattSprite);
    randomizeMatt(matt, playerEntity);

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && game_over)
        {
            game_over = false;
            player.reset();
            randomizeMatt(matt, player.getHead());
            direction = sf::Vector2f(0,0);
            std::string str_score = "Score: " + std::to_string(player.get_score());
            scoreText.setString(str_score);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            direction = sf::Vector2f(0,0);
        }

        if (clock.getElapsedTime().asMilliseconds() > 200)
        {
            if (direction != sf::Vector2f(0,0) && !game_over)
            {

                for (auto& entity : player.getBabies())
                {
                    if (player.getHead().wouldCollide(entity, direction))
                    {
                        game_over = true;
                        baby_sound.stop();
                        no_sound.play();
                    }
                }

                if (player.getHead().wouldBeOutOfBounds(direction, sf::Vector2f(GRID_WIDTH, GRID_HEIGHT)))
                {
                    game_over = true;
                    baby_sound.stop();
                    no_sound.play();
                }

                if (player.getHead().wouldCollide(matt, direction))
                {
                    randomizeMatt(matt, player.getHead());
                    
                    player.increment_score();
                    int randomNumber = std::rand() % 2;
                    auto babySprite = (randomNumber == 0) ? miniSprite : miniMattSprite;
                    
                    auto babySquare = player.getTail().getSquaredPosition();
                    Entity newPlayerEntity(GRID_SIZE, sf::Vector2f(0,0), babySprite);
                    newPlayerEntity.centerInSquare(babySquare);
                    player.move(direction);

                    player.addEntity(newPlayerEntity);
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
