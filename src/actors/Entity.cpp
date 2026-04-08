#include "Entity.hpp"

Entity::Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY)
    : animatedSprite(spriteCellCountX, spriteCellCountY, sheetLocation)
{
    health = hp;
    speed = spd;
    position = pos;
    verticalSpeed = 0.0f;
    horizontalSpeed = 0.0f;
    //spriteSheet = LoadTexture(sheetLocation);
    hitbox = {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight(), 
        animatedSprite.getCellWidth(), animatedSprite.getCellHeight()};
}

void Entity::draw(int action)
{
    animatedSprite.playAnimation(action);
    DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
    animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
    {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
}

void Entity::draw(int action, int frameCount)
{
    DrawRectangleRec(hitbox, PURPLE);
    animatedSprite.playAnimation(action, frameCount);
    DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
    animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
    {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
}

void Entity::updateHithox()
{
    hitbox.x = position.x-animatedSprite.getCellWidth()/2;
    hitbox.y = position.y-animatedSprite.getCellHeight();
}

int Entity::gethealth()
{
    return health;
}

float Entity::getspeed()
{
    return speed;
}

void Entity::sethealth(int hp)
{
    health = hp;
}

void Entity::setspeed(int spd)
{
    speed = spd;
}

float Entity::getPositionX()
{
    return position.x;
}

float Entity::getPositionY()
{
    return position.y;
}

void Entity::setPositionX(int newX)
{
    position.x = newX;
}

void Entity::setPositionY(int newY)
{
    position.y = newY;
}

float Entity::getVerticalSpeed()
{
    return verticalSpeed;
}

void Entity::setVerticalSpeed(float new_speed)
{
    verticalSpeed = new_speed;
}

float Entity::getHorizontalSpeed()
{
    return horizontalSpeed;
}

void Entity::setHorizontalSpeed(float new_speed)
{
    horizontalSpeed = new_speed;
}