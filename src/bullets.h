#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define DEBUG 1

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

        inline void renderBullets(sf::RenderWindow &window)
        {
            for (Bullet *bullet : m_bullets) {
                if (bullet->state != Bullet::dead) {
                    window.draw(bullet->sprite);
#if DEBUG
                    window.draw(bullet->debugAABB);
#endif
                }
            }
        }

        inline void updateBullets()
        {
            for (Bullet *bullet : m_bullets) {
                if ((bullet->sprite.getPosition()).y < 0) {
                    bullet->state = Bullet::dead;
                }

                if (bullet->state != Bullet::dead) {
                    bullet->sprite.move(0, bullet->speed);
#if DEBUG
                    bullet->debugAABB.move(0, bullet->speed);
#endif
                    bullet->aabb = bullet->sprite.getGlobalBounds();
                }
            }
        }

    private:
        sf::Texture m_bulletSheet;
        std::vector<Bullet*> m_bullets;
};
#endif
