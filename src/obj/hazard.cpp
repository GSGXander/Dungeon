#include "hazard.hpp"

hazard::hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent, int spriteCellCountX, int spriteCellCountY)
    : animatedSprite(spriteCellCountX, spriteCellCountY, sprite)
{
    position = pos;

    hitbox = {position.x - animatedSprite.getCellWidth()/2, position.y - animatedSprite.getCellHeight()/2,  
        static_cast<float>(animatedSprite.getCellWidth()), static_cast<float>(animatedSprite.getCellHeight())};
    
    playerAttack = plyAttack;
    isPersistent = persistent;
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

void hazard::draw()
{
    animatedSprite.playAnimation(0);
    DrawTextureRec(animatedSprite.getSpriteSheet(), (Rectangle) {animatedSprite.getSpriteX(), animatedSprite.getSpriteY(), 
    animatedSprite.getCellWidth(), animatedSprite.getCellHeight()}, 
    {position.x-animatedSprite.getCellWidth()/2, position.y-animatedSprite.getCellHeight()}, WHITE);
}

float hazard::getPositionX()
{
    return position.x;
}

float hazard::getPositionY()
{
    return position.y;
}

void hazard::setPositionX(int newX)
{
    position.x = newX;
}

void hazard::setPositionY(int newY)
{
    position.y = newY;
}