#pragma once
#include <raylib.h>

class hazard
{
    private:
        Rectangle hitbox;
        Vector2 position;
        Texture2D spriteSheet;
        bool playerAttack;
        bool isPersistent;
    
    public:
        hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent);

        bool isPlayerAttack();

        bool checkCollision(Rectangle entityHitbox);

        void draw(int frame);
};