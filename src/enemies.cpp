#include <iostream>
#include "enemies.h"

#define ENEMIES 20

Enemies::Enemies(const sf::Vector2u &bounds) :
    m_bounds(),
    m_enemies(ENEMIES, NULL)
{
    if (!m_enemySheet.loadFromFile("/home/mgodshall/hacking/c++/delta/assets/popcorn.png")) {
        std::cerr << "Unable to load enemy sprite sheet." << std::endl;
    }

    sf::IntRect rect(24, 0, 24, 28);
    for (int i = 0; i < ENEMIES; i++) {
        m_enemies[i] = new Enemy;
        m_enemies[i]->sprite.setTexture(m_enemySheet);
        m_enemies[i]->sprite.setTextureRect(rect);
        m_enemies[i]->state = Enemy::dead;
        m_enemies[i]->speed = 0.0;
    }

    m_bounds.left = 0;
    m_bounds.top = 0;
    m_bounds.width = bounds.x;
    m_bounds.height = bounds.y;
}

Enemies::~Enemies()
{
    for (Enemy *enemy : m_enemies) {
        delete enemy;
        enemy = NULL;
    }
}

void Enemies::renderEnemies(sf::RenderWindow &window)
{
    for (Enemy *enemy : m_enemies) {
        if (enemy->state != Enemy::dead) {
            window.draw(enemy->sprite);
        }
    }
}

void Enemies::spawnEnemy(const sf::Vector3f &origin)
{
    for (Enemy *enemy : m_enemies) {
        if (enemy->state == Enemy::dead) {
            enemy->state = Enemy::live;
            enemy->sprite.setPosition(origin.x, origin.y);
            enemy->speed = origin.z;
            break;
        }
    }
}

void Enemies::updateEnemies()
{
    for (Enemy *enemy : m_enemies) {
        if (!m_bounds.contains(enemy->sprite.getPosition())) {
            enemy->state = Enemy::dead;
        }

        if (enemy->state != Enemy::dead) {
            enemy->sprite.move(0, enemy->speed);
        }
    }
}
