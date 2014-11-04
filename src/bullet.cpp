#include <iostream>
#include "bullet.h"

#define NUM_BULLETS 100
#define SPEED -10

Bullets::Bullets() :
    m_bulletSheet(),
    m_bullets(NUM_BULLETS, NULL)
{
    if (!m_bulletSheet.loadFromFile("/home/mgodshall/hacking/c++/delta/assets/player_bullets.png")) {
        std::cerr << "Unable to load bullet texture sheet." << std::endl;
    } else {
        sf::IntRect rect(0, 0, 12, 13);
        for (int i = 0; i < NUM_BULLETS; i++) {
            m_bullets[i] = new Bullet;
            m_bullets[i]->sprite.setTexture(m_bulletSheet);
            m_bullets[i]->sprite.setTextureRect(rect);
            m_bullets[i]->state = dead;
        }
    }
}

Bullets::~Bullets()
{
    for (Bullet *bullet : m_bullets) {
        delete bullet;
    }
}

void Bullets::fire(const sf::Vector2f &origin)
{
    for (Bullet *bullet : m_bullets) {
        if (bullet->state == fired) {
            // XXX
            bullet->sprite.move(0, SPEED);
            continue;
        } else {
            bullet->state = fired;
            bullet->sprite.setPosition(origin);
            break;
        }
    }
}

void Bullets::renderBullets(sf::RenderWindow &window)
{
    for (Bullet *bullet : m_bullets) {
        sf::Vector2f pos = bullet->sprite.getPosition();

        if (pos.y < 0) {
            bullet->sprite.setPosition(0, 0);
            bullet->state = dead;
        }

        if (bullet->state != dead) {
            bullet->sprite.move(0, SPEED);
            window.draw(bullet->sprite);
        }
    }
}
