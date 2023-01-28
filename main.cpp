#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace sf;

class Bullet
{
public:
    Sprite shape;

    Bullet(Texture *texture, Vector2f position)
    {
        this->shape.setTexture(*texture);

        this->shape.setScale(0.09f, 0.09f);
        this->shape.setPosition(position);
    }

    // Bullet destructor
    ~Bullet(){

    };
};

class Player
{
    // pointer to texture to save memory
public:
    Sprite shape;
    Texture *texture;
    int HP;
    int HPMax;
    std::vector<Bullet> bullets;

    // Player constructor
    Player(Texture *texture)
    {
        // Player stats
        this->HPMax = 10;
        this->HP = this->HPMax;

        // dereference of pointer pointing to texture
        this->shape.setTexture(*texture);
        this->shape.setScale(0.2f, 0.2f);
        this->shape.setRotation(90.f);
        this->shape.setPosition(90.f, 150.f);
    }

    ~Player() {}
};
class Enemy
{
public:
    Sprite shape;

    int HP;
    int HPMax;

    Enemy(Texture *texture, Vector2u windowSize)
    {
        // rand() returns from 0 to 99 so HPMax of each enemy varies from 1 to 3
        this->HPMax = rand() % 3 + 1;
        this->HP = this->HPMax;

        // dereference of pointer pointing to texture
        this->shape.setTexture(*texture);
        this->shape.setScale(0.3f, 0.3f);

        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % windowSize.y + this->shape.getGlobalBounds().height - 10);
    }

    ~Enemy()
    {
    }
};

int main()
{
    // Game settings
    const float playerVelocity = 25;
    const float playerBulletsVelocity = 25;

    const int reloadTime = 15;
    int shootTimer = reloadTime - 1;

    const float enemyVelocity = 6;
    const int enemySpawnRate = 30;
    int enemySpawnTimer = 0;

    int score = 0;

    // time(NULL) returns unix date time format so each time there will be unique seed in each rand() ensuring best randomness
    srand(time(NULL));

    // Init fullscreen window
    RenderWindow window(VideoMode::getFullscreenModes()[0], "StarFighter", Style::Fullscreen);
    window.setFramerateLimit(60);

    // Init Font
    Font font;
    font.loadFromFile("./assets/Arial.ttf");

    // Init playerHpText
    Text playerHpText;
    playerHpText.setFont(font);
    playerHpText.setCharacterSize(20);
    playerHpText.setFillColor(Color::Red);

    // Init enemyHpText
    Text enemyHpText;
    enemyHpText.setFont(font);
    enemyHpText.setCharacterSize(18);
    enemyHpText.setFillColor(Color::Red);

    // Init scoreText
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(300.f, 10.f);

    // Init gameOverText
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width * 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);
    gameOverText.setString("GAME OVER");

    // Init player texture
    Texture playerTexture;
    playerTexture.loadFromFile("./assets/player.png");

    // Init enemy texture
    Texture enemyTexture;
    enemyTexture.loadFromFile("./assets/enemy.png");

    // Init bullet texture
    Texture bulletTexture;
    bulletTexture.loadFromFile("./assets/bullet.png");

    // Init player | & returns adress to memory later dereferenced in Player class constructor - same for all other classes
    Player player(&playerTexture);

    // Init enemies vector
    std::vector<Enemy> enemies;

    // Main event loop
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.KeyPressed && event.key.code == Keyboard::Escape)
                window.close();

            // player movement
            if (event.KeyPressed && event.key.code == Keyboard::W && player.HP > 0)
                player.shape.move(0.f, -playerVelocity);
            if (event.KeyPressed && event.key.code == Keyboard::S && player.HP > 0)
                player.shape.move(0.f, playerVelocity);
        }
        if (player.HP > 0)
        {
            playerHpText.setPosition(10.f, 10.f);
            playerHpText.setString("Player HP: " + std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

            // check player collision with window
            if (player.shape.getPosition().y <= 35) // top
                player.shape.setPosition(player.shape.getPosition().x, 35.f);
            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) // bottom
                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

            // reload timer
            if (shootTimer < reloadTime)
                shootTimer++;

            // shot bullet if reloaded
            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= reloadTime)
            {
                player.bullets.push_back(Bullet(&bulletTexture, Vector2f(player.shape.getPosition().x, player.shape.getPosition().y + 40)));
                shootTimer = 0;
            }

            // enemy spawn timer
            if (enemySpawnTimer < enemySpawnRate)
                enemySpawnTimer++;

            // spawn enemy and reset timer
            if (enemySpawnTimer >= enemySpawnRate)
            {
                enemies.push_back(Enemy(&enemyTexture, window.getSize()));
                enemySpawnTimer = 0;
            }

            // enemies update
            for (size_t i = 0; i < enemies.size(); i++)
            {
                // move each enemy
                enemies[i].shape.move(-enemyVelocity, 0);

                // Check if any of the enemies already left the window and erase them from memory
                if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
                {
                    enemies.erase(enemies.begin() + i);
                }

                // Check if enemy if intersecting with the player
                if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                {
                    enemies.erase(enemies.begin() + i);

                    // player takes damage from hit
                    player.HP--;
                }
            }

            // bullets update
            for (size_t i = 0; i < player.bullets.size(); i++)
            {
                // move player boolets
                player.bullets[i].shape.move(playerBulletsVelocity, 0.f);

                // Check if any of the player bullets already left the window and erase them from memory
                if (player.bullets[i].shape.getPosition().x > window.getSize().x)
                {
                    player.bullets.erase(player.bullets.begin() + i);
                }

                for (size_t j = 0; j < enemies.size(); j++)
                {
                    if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                    {
                        player.bullets.erase(player.bullets.begin() + i);

                        if (enemies[j].HP <= 1)
                        {
                            // enemy dies
                            score += enemies[j].HPMax;
                            enemies.erase(enemies.begin() + j);
                        }
                        else
                        {
                            // enemy takes damage
                            enemies[j]
                                .HP--;
                        }
                    }
                }
            }

            scoreText.setString("Enemies hit: " + std::to_string(score));
        }
        // Clear previous frame
        window.clear();

        // Draw player
        window.draw(player.shape);

        // Draw player bullets | size_t in iterator declaration for same type in loop boolean comparison
        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            window.draw(player.bullets[i].shape);
        }

        // Draw enemies
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemyHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
            enemyHpText.setPosition(enemies[i].shape.getPosition().x + 27, enemies[i].shape.getPosition().y - enemyHpText.getGlobalBounds().height - 8);

            // Draw enemy HP
            window.draw(enemyHpText);

            // Draw enemy
            window.draw(enemies[i].shape);
        }

        // Draw player HP
        window.draw(playerHpText);

        // Draw score
        window.draw(scoreText);

        // Draw gameover
        if (player.HP <= 0)
            window.draw(gameOverText);

        // Render new frame
        window.display();
    }

    return 0;
}
