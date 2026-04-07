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

void Player::movementKeyCheck(float delta)
{
    if(canMove)
    {
        if(IsKeyDown(KEY_A))
        {
            horizontalSpeed = -speed * delta;
        }   
        else if(IsKeyDown(KEY_D))
        {
            horizontalSpeed = speed * delta;
        }
        else
        {
            horizontalSpeed = 0;
        }

        if(IsKeyPressed(KEY_SPACE) && canJump)
        {
            verticalSpeed = 500.0f * delta;
        }
    }
}

void Player::playerCollisionCheck(Rectangle Rec)
{
    bool onGround = false;
    
    if((CheckCollisionPointRec({position.x, position.y - verticalSpeed}, Rec))) //floor collision
    {
        verticalSpeed = 0;
        position.y = Rec.y;
        onGround = true;
    }
    else if(CheckCollisionPointRec({position.x, position.y - hitbox.height}, Rec) && verticalSpeed > 0.0f) //ceiling collision
    {
        verticalSpeed = 0;
    }
    
    canJump = onGround;

    if(CheckCollisionPointRec({position.x - hitbox.width/2, position.y - hitbox.height/2}, Rec)) //Left wall collision
    {
        horizontalSpeed = 0;
        position.x = Rec.x + Rec.width + hitbox.width/2;
    }
    
    else if(CheckCollisionPointRec({position.x + hitbox.width/2, position.y - hitbox.height/2}, Rec)) //Right wall collision
    {
        horizontalSpeed = 0;
        position.x = Rec.x - hitbox.width/2;
    }
    
    DrawText(TextFormat("onGround: %d", onGround), 0,200,50,WHITE);
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