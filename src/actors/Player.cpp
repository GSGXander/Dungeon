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
    if(IsKeyDown(KEY_A))
    {
        horizontalSpeed = -speed * delta;
        if(direction < 0.0f)
        {
            direction = 1.0f;
        }
    }   
    else if(IsKeyDown(KEY_D))
    {
        horizontalSpeed = speed * delta;
        if(direction > 0.0f)
        {
            direction = -1.0f;
        }
    }
    else
    {
        horizontalSpeed = 0;
    }

    if(IsKeyPressed(KEY_SPACE) && canJump)
    {
        verticalSpeed = 750.0f * delta;
    }

}

void Player::playerCollisionCheck(Rectangle *Rec, int roomSize)
{
    bool onGround = false;
    
    for(int i = 0; i < roomSize; i++)
    {
        Rectangle *Rect = Rec + i;
        if((CheckCollisionPointRec({position.x, position.y - verticalSpeed}, *Rect))) //floor collision
        {
            verticalSpeed = 0;
            position.y = Rect->y;
            onGround = true;
        }
        else if(CheckCollisionPointRec({position.x, position.y - hitbox.height}, *Rect) && verticalSpeed > 0.0f) //ceiling collision
        {
            verticalSpeed = 0;
        }

        if(CheckCollisionPointRec({position.x - hitbox.width/2, position.y - hitbox.height/2}, *Rect)) //Left wall collision
        {
            horizontalSpeed = 0;
            position.x = Rect->x + Rect->width + hitbox.width/2;
        }
    
        else if(CheckCollisionPointRec({position.x + hitbox.width/2, position.y - hitbox.height/2}, *Rect)) //Right wall collision
        {
            horizontalSpeed = 0;
            position.x = Rect->x - hitbox.width/2;
        }
    }
    canJump = onGround;
    if(!canMove && onGround)
    {
        canMove = true;
    }
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