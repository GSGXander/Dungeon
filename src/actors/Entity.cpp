#include "Entity.hpp"

Entity::Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY, float resizeMultiplier)
    : animatedSprite(spriteCellCountX, spriteCellCountY, sheetLocation)
{
    health = hp;
    speed = spd;
    position = pos;
    verticalSpeed = 0.0f;
    horizontalSpeed = 0.0f;
    direction = -1.0f;
    //spriteSheet = LoadTexture(sheetLocation);
    float resizedWidth = animatedSprite.getCellWidth()*resizeMultiplier;
    float resizedHeight = animatedSprite.getCellHeight()*resizeMultiplier;
    hitbox = {position.x-resizedWidth/2, position.y-resizedHeight, 
        resizedWidth, resizedHeight};
    spriteScale = resizeMultiplier;
}

void Entity::draw(int action)
{
    //DrawRectangleRec(hitbox, GREEN);
    animatedSprite.playAnimation(action);
    DrawTexturePro(animatedSprite.getSpriteSheet(),
    {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(),direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()},
    {position.x, position.y, animatedSprite.getCellWidth()*spriteScale, animatedSprite.getCellHeight()*spriteScale},
    {(animatedSprite.getCellWidth()*spriteScale)/2, animatedSprite.getCellHeight()*spriteScale},
    0.0f, WHITE);
}

void Entity::draw(int action, int frameCount)
{
    //DrawRectangleRec(hitbox, GREEN);
    animatedSprite.playAnimation(action, frameCount);
    DrawTexturePro(animatedSprite.getSpriteSheet(),
    {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(),direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()},
    {position.x, position.y, animatedSprite.getCellWidth()*spriteScale, animatedSprite.getCellHeight()*spriteScale},
    {(animatedSprite.getCellWidth()*spriteScale)/2, animatedSprite.getCellHeight()*spriteScale},
    0.0f, WHITE);
}

void Entity::draw(int action, int frameCount, int speed)
{
    //DrawRectangleRec(hitbox, GREEN);
    animatedSprite.playAnimation(action, frameCount, speed);
    DrawTexturePro(animatedSprite.getSpriteSheet(),
    {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(),direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()},
    {position.x, position.y, animatedSprite.getCellWidth()*spriteScale, animatedSprite.getCellHeight()*spriteScale},
    {(animatedSprite.getCellWidth()*spriteScale)/2, animatedSprite.getCellHeight()*spriteScale},
    0.0f, WHITE);
}

bool Entity::drawEX(int action, int frameCount, int speed, Color tint, bool playOnce)
{
    bool animationPlaying = true;

    if(!playOnce)
    {
        animatedSprite.playAnimation(action, frameCount, speed);
        DrawTexturePro(animatedSprite.getSpriteSheet(),
        {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(),direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()},
        {position.x, position.y, animatedSprite.getCellWidth()*spriteScale, animatedSprite.getCellHeight()*spriteScale},
        {(animatedSprite.getCellWidth()*spriteScale)/2, animatedSprite.getCellHeight()*spriteScale},
        0.0f, WHITE);
    }
    else
    {
        if(!animatedSprite.playAnimationOnce(action, frameCount, speed))
        {
            animatedSprite.playAnimation(action, frameCount, speed);
            DrawTexturePro(animatedSprite.getSpriteSheet(),
            {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(),direction*animatedSprite.getCellWidth(), animatedSprite.getCellHeight()},
            {position.x, position.y, animatedSprite.getCellWidth()*spriteScale, animatedSprite.getCellHeight()*spriteScale},
            {(animatedSprite.getCellWidth()*spriteScale)/2, animatedSprite.getCellHeight()*spriteScale},
            0.0f, WHITE);
        }
        else
        {
            animationPlaying = false;
        }
    }
    return animationPlaying;
}

void Entity::updateHithox()
{
    hitbox.x = position.x-(animatedSprite.getCellWidth()*spriteScale)/2;
    hitbox.y = position.y-animatedSprite.getCellHeight()*spriteScale;
}

Rectangle Entity::getHitbox()
{
    return hitbox;
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

float Entity::getDirection()
{
    return direction;
}

void Entity::setDirection(float newDirection)
{
    direction = newDirection;
}

float Entity::getSpriteScale()
{
    return spriteScale;
}

void Entity:: setSpriteScale(float new_scale)
{
    spriteScale = new_scale;
}