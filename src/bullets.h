#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum State {
    fired,
    dead
};

struct Bullet {
    State state;
    sf::Sprite sprite;
};

class Bullets {
    public:

        Bullets();
        ~Bullets();

        void fire(const sf::Vector2f &origin);
        void renderBullets(sf::RenderWindow &window);
        void updateBullets();

    private:
        sf::Texture m_bulletSheet;
        std::vector<Bullet*> m_bullets;
};
#endif
