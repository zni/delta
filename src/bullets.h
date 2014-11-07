#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct Bullet {
    enum State {
        fired,
        dead
    };

    State state;
    sf::FloatRect aabb;
    sf::Sprite sprite;
    sf::RectangleShape debugAABB;
    float speed;
};

class Bullets {
    public:

        Bullets();
        ~Bullets();

        void fire(const sf::Vector2f &origin, const float &speed);
        void renderBullets(sf::RenderWindow &window);
        void updateBullets();

    private:
        sf::Texture m_bulletSheet;
        std::vector<Bullet*> m_bullets;
};
#endif
