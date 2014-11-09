#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "player.h"
#include "bullets.h"
#include "enemies.h"

// FIXME this is temporary. STOP procrastinating.
void checkCollisions(std::vector<Enemy*> *enemies, std::vector<Bullet*> *bullets)
{
    for (Enemy *enemy : *enemies) {
        if (enemy->state == Enemy::dead) {
            continue;
        }

        for (Bullet *bullet : *bullets) {
            if (bullet->state == Bullet::fired) {
                if (bullet->aabb.intersects(enemy->aabb)) {
                    bullet->state = Bullet::dead;
                    enemy->state = Enemy::dead;
                }
            }
        }
    }
}

int main()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode mode = modes[modes.size() - 1];
    sf::RenderWindow window(mode, "delta", sf::Style::Fullscreen);

    Enemies enemies(window.getSize());
    Bullets bullets;
    Player player("/home/mgodshall/hacking/c++/delta/assets/raiden_ship.png", &bullets);
    player.setPosition(160, 220);
    window.setKeyRepeatEnabled(false);

    sf::Vector3f spawnOrigin(60, 0, 5);
    sf::Time spawnTime;
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {

                // FIXME need a way out
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else {
                    player.handleKeyPress(event.key.code, true);
                }
            }
            if (event.type == sf::Event::KeyReleased)
                player.handleKeyPress(event.key.code, false);
        }

        if (clock.getElapsedTime().asMilliseconds() >= 16) {
            spawnTime += clock.getElapsedTime();

            // Update
            player.updateMovement();
            bullets.updateBullets();

            // FIXME debug spawner
            if (spawnTime.asSeconds() >= 2) {
                spawnTime = sf::Time::Zero;
                spawnOrigin.x = 60;
                enemies.spawnEnemy(spawnOrigin);
                spawnOrigin.x = 260;
                enemies.spawnEnemy(spawnOrigin);
                spawnOrigin.x = 460;
                enemies.spawnEnemy(spawnOrigin);
                enemies.updateEnemies();
            } else {
                enemies.updateEnemies();
            }

            // FIXME check collisions
            checkCollisions(enemies.enemies(), bullets.bullets());

            // Render
            window.clear();
            bullets.renderBullets(window);
            enemies.renderEnemies(window);
            window.draw(player.sprite());
            window.display();

            clock.restart();
        }
    }

    return 0;
}
