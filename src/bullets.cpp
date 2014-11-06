#include <iostream>
#include "bullets.h"

#define NUM_BULLETS 100

Bullets::Bullets() :
    m_bulletSheet(),
    m_bullets(NUM_BULLETS, NULL)
{
    if (!m_bulletSheet.loadFromFile("/home/mgodshall/hacking/c++/delta/assets/player_bullets.png")) {
        std::cerr << "Unable to load bullet texture sheet." << std::endl;
    } else {
        sf::IntRect rect(24, 0, 12, 13);
        for (int i = 0; i < NUM_BULLETS; i++) {
            m_bullets[i] = new Bullet;
            m_bullets[i]->sprite.setTexture(m_bulletSheet);
            m_bullets[i]->sprite.setTextureRect(rect);
            m_bullets[i]->state = Bullet::dead;
            m_bullets[i]->speed = 0;
        }
    }
}

Bullets::~Bullets()
{
    for (Bullet *bullet : m_bullets) {
        delete bullet;
        bullet = NULL;
    }
}

void Bullets::fire(const sf::Vector2f &origin, const float &speed)
{
    for (Bullet *bullet : m_bullets) {
        if (bullet->state != Bullet::fired) {
            bullet->state = Bullet::fired;
            bullet->sprite.setPosition(origin);
            bullet->speed = speed;
            break;
        }
    }
}

void Bullets::renderBullets(sf::RenderWindow &window)
{
    for (Bullet *bullet : m_bullets) {
        if (bullet->state != Bullet::dead) {
            window.draw(bullet->sprite);
        }
    }
}

void Bullets::updateBullets()
{
    for (Bullet *bullet : m_bullets) {
        if ((bullet->sprite.getPosition()).y < 0) {
            bullet->state = Bullet::dead;
        }

        if (bullet->state != Bullet::dead) {
            bullet->sprite.move(0, bullet->speed);
        }
    }
}
