#include "hazard.hpp"

hazard::hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent, int spriteCellCountX, int spriteCellCountY)
    : animatedSprite(spriteCellCountX, spriteCellCountY, sprite)
{
    position = pos;

    hitbox = {position.x - animatedSprite.getCellWidth()/2, position.y - animatedSprite.getCellHeight()/2,  
        static_cast<float>(animatedSprite.getCellWidth()), static_cast<float>(animatedSprite.getCellHeight())};
    
    playerAttack = plyAttack;
    isPersistent = persistent;
    activeTimer = 0;
}

bool hazard::isPlayerAttack()
{
    return playerAttack;
}

bool hazard::checkCollision(Rectangle entityHitbox)
{
    if(CheckCollisionRecs(hitbox, entityHitbox))
    {
        return true;
    }
    return false;
}

void hazard::hazardRoomCollisionCheck(Rectangle *Rec, int roomSize)
{
    for(int i = 0; i < roomSize; i++)
    {
        Rectangle *Rect = Rec + i;
        if((CheckCollisionPointRec({position.x, position.y - verticalSpeed}, *Rect))) //floor collision
        {
            verticalSpeed = -verticalSpeed;
            position.y = Rect->y;
        }
        else if(CheckCollisionPointRec({position.x, position.y - hitbox.height}, *Rect) && verticalSpeed > 0.0f) //ceiling collision
        {
            verticalSpeed = -verticalSpeed;
        }

        if(CheckCollisionPointRec({position.x - hitbox.width/2, position.y - hitbox.height/2}, *Rect)) //Left wall collision
        {
            horizontalSpeed = -horizontalSpeed;
            position.x = Rect->x + Rect->width + hitbox.width/2;
        }
    
        else if(CheckCollisionPointRec({position.x + hitbox.width/2, position.y - hitbox.height/2}, *Rect)) //Right wall collision
        {
            horizontalSpeed = -horizontalSpeed;
            position.x = Rect->x - hitbox.width/2;
        }
    }
}

void hazard::draw()
{
    animatedSprite.playAnimation(0);
    DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
    animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
    {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
}

bool hazard::timedDraw(int action, int frames, int frameSpeed)
{
    bool animationPlaying = true;

    if(!animatedSprite.playAnimationOnce(action, frames, frameSpeed))
    {
        //DrawRectangleRec(hitbox, RED);
        DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
        direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
        {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
    }
    else
    {
        animationPlaying = false;
    }
    return animationPlaying;
}

float hazard::getPositionX()
{
    return position.x;
}

float hazard::getPositionY()
{
    return position.y;
}

void hazard::setPositionX(float newX)
{
    position.x = newX;
    hitbox.x = newX - animatedSprite.getCellWidth()/2.0f;
}

void hazard::setPositionY(float newY)
{
    position.y = newY;
    hitbox.y = newY - animatedSprite.getCellHeight();
}

float hazard::getDirection()
{
    return direction;
}

void hazard::setDirection(float newDirection)
{
    direction = newDirection;
}

int hazard::getActiveTimer()
{
    return activeTimer;
}

void hazard::setActiveTimer(int new_timer)
{
    activeTimer = new_timer;
}

bool hazard::getPersistence()
{
    return isPersistent;
}

float hazard::getVerticalSpeed()
{
    return verticalSpeed;
}

void hazard::setVerticalSpeed(float new_speed)
{
    verticalSpeed = new_speed;
}

float hazard::getHorizontalSpeed()
{
    return horizontalSpeed;
}

void hazard::setHorizontalSpeed(float new_speed)
{
    horizontalSpeed = new_speed;
}