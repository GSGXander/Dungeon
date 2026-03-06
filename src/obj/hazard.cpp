#include "hazard.hpp"

hazard::hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent)
{
    position = pos;
    spriteSheet = LoadTexture(sprite);

    hitbox = {position.x - spriteSheet.width/2, position.y - spriteSheet.height/2,  
        static_cast<float>(spriteSheet.width), static_cast<float>(spriteSheet.height)};
    
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

void hazard::draw(int frame)
{
    DrawTextureRec(spriteSheet, (Rectangle) {0.0f + (frame * 150), 0.0f + (frame * 150), 150.0f, 150.0f}, {position.x - 75.0f, position.y - 150.0f}, WHITE);
}