#include <iostream>
#include "player.h"

#define SPEED 8

Player::Player(const std::string &image, Bullets *bullets) :
    m_playerSprite(),
    m_shipTexture(),
    m_keymap(),
    m_bullets(bullets)
{
    if (!m_shipTexture.loadFromFile(image)) {
        std::cerr << "Unable to load player texture: " << image << std::endl;
    } else {
        m_playerSprite.setTexture(m_shipTexture);
        m_playerSprite.setOrigin(10, 16);
    }

    // Initialize keymap
    m_keymap[sf::Keyboard::W] = false;
    m_keymap[sf::Keyboard::S] = false;
    m_keymap[sf::Keyboard::A] = false;
    m_keymap[sf::Keyboard::D] = false;
    m_keymap[sf::Keyboard::Space] = false;
}

Player::~Player() { }


/**
 * Move player to offset xpos + x, ypos + y.
 *
 * x - x offset
 * y - y offset
 */
void Player::move(const float &x, const float &y)
{
    m_playerSprite.move(x, y);
}

void Player::setPosition(const float &x, const float &y)
{
    m_playerSprite.setPosition(x, y);
}

/**
 * Handle incoming keycodes and pressed/released state.
 *
 * key     - the key belonging to the event.
 * pressed - was the key pressed or released?
 */
void Player::handleKeyPress(const sf::Keyboard::Key &key, const bool &pressed)
{
    m_keymap[key] = pressed;
}

/**
 * Return the player's sprite.
 */
sf::Sprite Player::sprite() const
{
    return m_playerSprite;
}

/**
 * Update movement based on keymap state.
 */
void Player::updateMovement()
{
    if (m_keymap[sf::Keyboard::W]) {
        this->move(0, -SPEED);
    }
    if (m_keymap[sf::Keyboard::S]) {
        this->move(0, SPEED);
    }
    if (m_keymap[sf::Keyboard::A]) {
        this->move(-SPEED, 0);
    }
    if (m_keymap[sf::Keyboard::D]) {
        this->move(SPEED, 0);
    }
    if (m_keymap[sf::Keyboard::Space]) {
        m_bullets->fire(m_playerSprite.getPosition(), -20);
    }
}
