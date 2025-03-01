#include "player.h"

Player::Player(const char *path, SDL_Renderer *renderer, int maxHealth, vec2 position)
    : Object(path, renderer, position), maxHealth(maxHealth), health(maxHealth)
{
    maxSpeed = 100;
    velocity = vec2(0, 0);
}

void Player::incHealth(int value)
{
    int newHealth = health + value;
    if (newHealth > maxHealth) {
        health = maxHealth;
    } else {
        health = newHealth;
    }
}

bool Player::decHealth(int value)
{
    int newHealth = health - value;
    if (newHealth < 0) {
        health = 0;
        return true;
    } else {
        health = newHealth;
        return false;
    }
}

void Player::setHealth(int value)
{
    health = value;
}

void Player::setVelocity(vec2 targetVelocity)
{
    velocity = targetVelocity;
}

int Player::getHealth()
{
    return health;
}

float Player::getMaxSpeed()
{
    return maxSpeed;
}

vec2 Player::getVelocity()
{
    return velocity;
}