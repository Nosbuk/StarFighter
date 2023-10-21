#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <random>

#include "Enemy.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

using namespace sf;

class Game
{

private:
    int reloadTime;
    int shootTimer;

    int enemySpawnRate;
    int enemySpawnTimer;

    int score;

    RenderWindow window;

    Event event;

    Player player;

    std::vector<Enemy> enemies;

    Font font;

    Text playerHpText;

    Text enemyHpText;

    Text scoreText;

    Text gameOverText;

    Texture playerTexture;

    Texture enemyTexture;

    Texture bulletTexture;

public:
    Game() : window(VideoMode::getFullscreenModes()[0], "StarFighter", Style::Fullscreen)
    {
        this->reloadTime = 15;
        this->shootTimer = this->reloadTime - 1;

        this->enemySpawnRate = 30;
        this->enemySpawnTimer = 0;

        this->score = 0;

        srand(time(NULL));

        window.setFramerateLimit(60);

        font.loadFromFile("./assets/Arial.ttf");

        playerHpText.setFont(font);
        playerHpText.setCharacterSize(20);
        playerHpText.setFillColor(Color::Red);
        playerHpText.setPosition(10.f, 10.f);

        enemyHpText.setFont(font);
        enemyHpText.setCharacterSize(18);
        enemyHpText.setFillColor(Color::Red);

        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(Color::Yellow);
        scoreText.setPosition(300.f, 10.f);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width * 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);
        gameOverText.setString("GAME OVER");

        playerTexture.loadFromFile("./assets/player.png");
        player.setTexture(&playerTexture);

        enemyTexture.loadFromFile("./assets/enemy.png");

        bulletTexture.loadFromFile("./assets/bullet.png");
    }

    ~Game()
    {
    }

    int run()
    {
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (event.KeyPressed && event.key.code == Keyboard::Escape)
                    window.close();

                if (event.KeyPressed && event.key.code == Keyboard::W && player.getHP() > 0)
                    player.moveUp();
                if (event.KeyPressed && event.key.code == Keyboard::S && player.getHP() > 0)
                    player.moveDown();
            }

            playerHpText.setString("Player HP: " + std::to_string(player.getHP()) + "/" + std::to_string(player.getHPMax()));

            if (player.getHP() > 0)
            {
                if (player.getPosition().y <= 35)
                    player.shape.setPosition(player.getPosition().x, 35.f);
                if (player.getPosition().y >= window.getSize().y - player.getGlobalBounds().height)
                    player.shape.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);

                if (shootTimer < reloadTime)
                    shootTimer++;

                if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= reloadTime)
                {
                    player.bullets.push_back(Bullet(&bulletTexture, Vector2f(player.getPosition().x, player.getPosition().y + 40.f)));
                    shootTimer = 0;
                }

                if (enemySpawnTimer < enemySpawnRate)
                    enemySpawnTimer++;

                if (enemySpawnTimer >= enemySpawnRate)
                {
                    enemies.push_back(Enemy(&enemyTexture, window.getSize()));
                    enemySpawnTimer = 0;
                }

                for (size_t i = 0; i < enemies.size(); i++)
                {
                    enemies[i].moveLeft();

                    if (enemies[i].getPosition().x <= 0 - enemies[i].getGlobalBounds().width)
                    {
                        enemies.erase(enemies.begin() + i);
                    }

                    if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds()))
                    {
                        enemies.erase(enemies.begin() + i);

                        player.takeHit();
                    }
                }

                for (size_t i = 0; i < player.bullets.size(); i++)
                {
                    player.bullets[i].moveRight();

                    if (player.bullets[i].getPosition().x > window.getSize().x)
                    {
                        player.bullets.erase(player.bullets.begin() + i);
                    }

                    for (size_t j = 0; j < enemies.size(); j++)
                    {
                        if (player.bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                        {
                            player.bullets.erase(player.bullets.begin() + i);

                            if (enemies[j].getHP() <= 1)
                            {
                                score += enemies[j].HPMax;
                                enemies.erase(enemies.begin() + j);
                            }
                            else
                            {
                                enemies[j].takeHit();
                            }
                        }
                    }
                }

                scoreText.setString("Enemies hit: " + std::to_string(score));
            }
            window.clear();

            window.draw(player.shape);

            for (size_t i = 0; i < player.bullets.size(); i++)
            {
                window.draw(player.bullets[i].shape);
            }

            for (size_t i = 0; i < enemies.size(); i++)
            {
                enemyHpText.setString(std::to_string(enemies[i].getHP()) + "/" + std::to_string(enemies[i].HPMax));
                enemyHpText.setPosition(enemies[i].getPosition().x + 27, enemies[i].getPosition().y - enemyHpText.getGlobalBounds().height - 8);

                window.draw(enemyHpText);

                window.draw(enemies[i].shape);
            }

            window.draw(playerHpText);

            window.draw(scoreText);

            if (player.getHP() <= 0)
                window.draw(gameOverText);

            window.display();
        }
        return 0;
    }
};
