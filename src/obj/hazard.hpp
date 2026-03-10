#pragma once
#include <raylib.h>
#include "src/core/animationHandler.hpp"

class hazard
{
    private:
        Rectangle hitbox;
        Vector2 position;
        animationHandler animatedSprite;
        bool playerAttack;
        bool isPersistent;
    
    public:
        hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent, int spriteCellCountX, int spriteCellCountY);

        bool isPlayerAttack();

        bool checkCollision(Rectangle entityHitbox);

        void draw();
};