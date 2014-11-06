#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "player.h"
#include "bullet.h"
#include "enemies.h"

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

    sf::Vector3f spawnOrigin(160, 0, 9);
    sf::Time spawnTime;
    sf::Clock clock;
    int x = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
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
            x = (x + 20) % 320;
            spawnOrigin.x = x;

            // Update
            player.updateMovement();
            bullets.updateBullets();
            if (spawnTime.asMilliseconds() >= 200) {
                spawnTime = sf::Time::Zero;
                enemies.spawnEnemy(spawnOrigin);
                enemies.updateEnemies();
            } else {
                enemies.updateEnemies();
            }

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
