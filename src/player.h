#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "bullet.h"

class Player
{
    public:
        Player(const std::string &image, Bullets *bullets);
        ~Player();

        void handleKeyPress(const sf::Keyboard::Key &key, const bool &pressed);
        void move(const float &x, const float &y);
        void setPosition(const float &x, const float &y);
        void updateMovement();

        sf::Sprite sprite() const;

    private:
        sf::Sprite m_playerSprite;
        sf::Texture m_shipTexture;
        std::map<sf::Keyboard::Key, bool> m_keymap;
        Bullets *m_bullets;
};
#endif
