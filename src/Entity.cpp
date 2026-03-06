#include "Entity.hpp"

Entity::Entity(int hp, float spd, Vector2 pos, const char *sheetLocation)
{
    health = hp;
    speed = spd;
    position = pos;
    spriteSheet = LoadTexture(sheetLocation);
    hitbox = {position.x - 75.0f, position.y - 150.0f, 150.0f, 150.0f};
}

void Entity::draw(int frame, int action)
{
    DrawTextureRec(spriteSheet, (Rectangle) {0.0f + (frame * 150), 0.0f + (frame * 150), 150.0f, 150.0f}, {position.x - 75.0f, position.y - 150.0f}, WHITE);
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