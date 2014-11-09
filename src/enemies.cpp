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

        // aabb
        sf::FloatRect bounds = m_enemies[i]->sprite.getGlobalBounds();
        sf::Vector2f size(bounds.width, bounds.height);
        m_enemies[i]->aabb = bounds;


        // XXX debug aabb
        m_enemies[i]->debugAABB.setFillColor(sf::Color::Transparent);
        m_enemies[i]->debugAABB.setOutlineColor(sf::Color::Yellow);
        m_enemies[i]->debugAABB.setOutlineThickness(1.0);
        m_enemies[i]->debugAABB.setSize(size);
        m_enemies[i]->debugAABB.setPosition(m_enemies[i]->sprite.getPosition());
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

std::vector<Enemy*>* Enemies::enemies()
{
    return &m_enemies;
}

void Enemies::renderEnemies(sf::RenderWindow &window)
{
    for (Enemy *enemy : m_enemies) {
        if (enemy->state != Enemy::dead) {
            window.draw(enemy->sprite);
            window.draw(enemy->debugAABB);
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

            // XXX
            enemy->debugAABB.setPosition(origin.x, origin.y);

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
            enemy->debugAABB.move(0, enemy->speed);
            enemy->aabb = enemy->sprite.getGlobalBounds();
        }
    }
}
