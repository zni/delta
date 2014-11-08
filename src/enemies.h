#ifndef ENEMIES_H
#define ENEMIES_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct Enemy {
    enum State { live, dead };
    State state;
    sf::FloatRect aabb;
    sf::Sprite sprite;
    sf::RectangleShape debugAABB;
    float speed;
};

class Enemies {
    public:
        Enemies(const sf::Vector2u &bounds);
        ~Enemies();

        void renderEnemies(sf::RenderWindow &window);
        void spawnEnemy(const sf::Vector3f &origin);
        void updateEnemies();

    private:
        sf::Texture m_enemySheet;
        sf::FloatRect m_bounds;
        std::vector<Enemy*> m_enemies;
};

#endif
