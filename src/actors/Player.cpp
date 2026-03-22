#include "Player.hpp"

Player::Player(int dCounter, float sUpgrade, int hUpgrade, Vector2 position, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY)
    : Entity(3 + hUpgrade, 350.0f + sUpgrade, position, sheetLocation, spriteCellCountX, spriteCellCountY)
{
    deathCounter = dCounter;
    spdUpgrade = sUpgrade;
    hlthUpgrade = hUpgrade;
    invc = false;
    canMove = true;
    canAttack = true;
    canJump = true;
}

void Player::playerMove()
{
    if(canMove)
    {
        if(IsKeyDown(KEY_A))
        {
            position.x -= speed * GetFrameTime();
            draw(1);
        }   
        else if(IsKeyDown(KEY_D))
        {
            position.x += speed * GetFrameTime();
            draw(1);
        }
        else
        {
            draw(0, 1);
        }

        if(IsKeyPressed(KEY_SPACE) && canJump)
        {
            verticalSpeed = 300.0f;
            canJump = false;
        }

        if(!canJump)
        {
            position.y -= verticalSpeed * GetFrameTime();
            verticalSpeed -= 500.0f * GetFrameTime();
        }
        updateHithox();
    }
}

bool Player::playerCollisionCheck(Rectangle Rec)
{
    if(CheckCollisionRecs(Rec, hitbox))
    {
        verticalSpeed = 0.0f;
        canJump = true;
        return true;
    }
    canJump = false;
    return false;
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