#include "Player.hpp"

Player::Player(int dCounter, float sUpgrade, int hUpgrade, Vector2 position, const char *sheetLocation)
    : Entity(3 + hUpgrade, 3.0f + sUpgrade, position, sheetLocation)
{
    deathCounter = dCounter;
    spdUpgrade = sUpgrade;
    hlthUpgrade = hUpgrade;
    invc = false;
    canMove = true;
    canAttack = true;
    canJump = true;
}

int Player::getDeaths()
{
    return deathCounter;
}

void Player::setDeaths(int newDeath)
{
    deathCounter = newDeath;
}

bool Player::isInvc()
{
    return invc;
}

void Player::setInvc(bool boo)
{
    invc = boo;
}

bool Player::ableToMove()
{
    return canMove;
}

void Player::setCanMove(bool boo)
{
    canMove = boo;
}

bool Player::ableToAttack()
{
    return canAttack;
}

void Player::setCanAttack(bool boo)
{
    canAttack = boo;
}

bool Player::ableToJump()
{
    return canJump;
}

void Player::setCanJump(bool boo)
{
    canJump = boo;
}