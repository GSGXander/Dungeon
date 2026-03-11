#include "Entity.hpp"

Entity::Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY)
    : animatedSprite(spriteCellCountX, spriteCellCountY, sheetLocation)
{
    health = hp;
    speed = spd;
    position = pos;
    //spriteSheet = LoadTexture(sheetLocation);
    hitbox = {position.x - 75.0f, position.y - 150.0f, 150.0f, 150.0f};
}

void Entity::draw(int action)
{
    animatedSprite.playAnimation(action);
    DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
    animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
    {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
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