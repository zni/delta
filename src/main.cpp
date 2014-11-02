#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 600), "delta");
    Player player("/home/mgodshall/hacking/c++/delta/assets/raiden_ship.png");
    player.setPosition(200, 500);
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                player.handleKeyPress(event.key.code, true);
            if (event.type == sf::Event::KeyReleased)
                player.handleKeyPress(event.key.code, false);
        }

        if (clock.getElapsedTime().asMilliseconds() > 1) {
            player.updateMovement();

            window.clear();
            window.draw(player.sprite());
            window.display();
            clock.restart();
        }
    }

    return 0;
}
