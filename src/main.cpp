#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "grid.hpp"
#include "entity.hpp"
#include "input.hpp"
#include "player.hpp"
#include "setup.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int GRID_WIDTH = 800;
const int GRID_HEIGHT = 700;
const int GRID_SIZE = 100;
const float GAME_SPEED = 1.f;
bool game_over = false;


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    
    Grid grid(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);

    // LOAD PLAYER TEXTURE
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("avatar.png")) {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }

    // LOAD MATT TEXTURE
    sf::Texture mattTexture;
    if (!mattTexture.loadFromFile("matt.png")) {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }

    // LOAD PLAYER SPRITE
    sf::Sprite playerSprite;
    setUpSprite(playerSprite, playerTexture, GRID_SIZE, 0.67, 0.87);

    // LOAD MATT SPRITE
    sf::Sprite mattSprite;
    setUpSprite(mattSprite, mattTexture, GRID_SIZE, 0.7, 0.9);

    // LOAD MINI PLAYER SPRITE
    sf::Sprite miniSprite;
    setUpSprite(miniSprite, playerTexture, GRID_SIZE, 0.37, 0.37);

    // LOAD MINI MATT SPRITE
    sf::Sprite miniMattSprite;
    setUpSprite(miniMattSprite, mattTexture, GRID_SIZE, 0.4, 0.4);

    // CREATE PLAYER ENTITY
    sf::Vector2f playerSquare(3,3);
    Entity playerEntity(GRID_SIZE, sf::Vector2f(0,0), playerSprite);
    playerEntity.centerInSquare(playerSquare);
    Player player(playerEntity);

    // CREATE MATT ENTITY
    sf::Vector2f mattPos(0,0);
    Entity matt(GRID_SIZE, mattPos, mattSprite);
    do {
        matt.randomizePosition(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);
    } while (matt.getSquaredPosition() == player.getHead().getSquaredPosition());

    // LOAD FONT
    sf::Font font;
    font.loadFromFile("TimesNewRoman.otf");

    // CREATE SCORE TEXT
    sf::Text scoreText;
    setUpText(scoreText, font, "Score: 0", 24, sf::Color::White, sf::Vector2f(10, 710));

    // CREATE GAME OVER TEXT
    sf::Text gameOverText;
    setUpText(gameOverText, font, "Game Over!", 48, sf::Color::White, sf::Vector2f(300, 300));

    sf::Text highScoreText;
    setUpText(highScoreText, font, "High Score: 0", 24, sf::Color::White, sf::Vector2f(200, 710));

    // LOAD BABY SOUND FILE
    sf::SoundBuffer baby_buffer;
    if (!baby_buffer.loadFromFile("baby1.mp3"))
        return -1;

    // CREATE BABY SOUND OBJECT
    sf::Sound baby_sound;
    baby_sound.setBuffer(baby_buffer);
    
    // LOAD NO SOUND FILE
    sf::SoundBuffer no_buffer;
    if (!no_buffer.loadFromFile("no1.mp3"))
        return -1;

    // CREATE NO SOUND OBJECT
    sf::Sound no_sound;
    no_sound.setBuffer(no_buffer);

    // GAME CLOCK USED FOR MOVEMENT
    sf::Clock clock;

    // INITIALIZE DIRECTION AND MOVEMENT DIRECTION
    sf::Vector2f direction(0, 0);
    sf::Vector2f movement_direction(0, 0);

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // CHANGE DIRECTION BASED ON INPUT
        direction = handleInput(movement_direction, direction);

        // RESET GAME
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && game_over)
        {
            game_over = false;
            player.reset();
            do {
                matt.randomizePosition(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);
            } while (matt.getSquaredPosition() == player.getHead().getSquaredPosition());
            direction = sf::Vector2f(0,0);
            movement_direction = sf::Vector2f(0,0);
            std::string str_score = "Score: " + std::to_string(player.get_score());
            scoreText.setString(str_score);
        }

        // PAUSE GAME
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            direction = sf::Vector2f(0,0);
        }

        // MOVE PLAYER BASED ON GAME SPEED
        if (clock.getElapsedTime().asMilliseconds() > 200/GAME_SPEED)
        {
            if (direction != sf::Vector2f(0,0) && !game_over)
            {

                for (auto& entity : player.getBabies())
                {
                    if (player.getHead().wouldCollide(entity, direction))
                    {
                        game_over = true;
                        player.setHighScore();
                        highScoreText.setString("High Score: " + std::to_string(player.getHighScore()));
                        baby_sound.stop();
                        no_sound.play();
                    }
                }
                // END GAME IF PLAYER WOULD BE OUT OF BOUNDS
                if (player.getHead().wouldBeOutOfBounds(direction, sf::Vector2f(GRID_WIDTH, GRID_HEIGHT)))
                {
                    game_over = true;
                    player.setHighScore();
                    highScoreText.setString("High Score: " + std::to_string(player.getHighScore()));
                    baby_sound.stop();
                    no_sound.play();
                }
                // INCREMENT SCORE AND ADD BABY IF PLAYER WOULD COLLIDE WITH MATT
                if (player.getHead().wouldCollide(matt, direction))
                {

                    do {
                        matt.randomizePosition(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);
                    } while (matt.getSquaredPosition() == player.getHead().getSquaredPosition());
                    
                    player.increment_score();
                    int randomNumber = std::rand() % 2;
                    auto babySprite = (randomNumber == 0) ? miniSprite : miniMattSprite;
                    
                    auto babySquare = player.getTail().getSquaredPosition();
                    Entity newPlayerEntity(GRID_SIZE, sf::Vector2f(0,0), babySprite);
                    newPlayerEntity.centerInSquare(babySquare);
                    movement_direction = direction;
                    player.move(direction);

                    player.addEntity(newPlayerEntity);
                    baby_sound.play();
                    std::string str_score = "Score: " + std::to_string(player.get_score());
                    scoreText.setString(str_score);
                    
                }
                // MOVE PLAYER
                else {
                    player.move(direction);
                    movement_direction = direction;
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
            window.draw(highScoreText);
        }

        else {
            window.draw(gameOverText);
            window.draw(highScoreText);
        }
        
        window.display();
    }
}
