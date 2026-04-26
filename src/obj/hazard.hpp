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
        float direction;
    
    public:
        hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent, int spriteCellCountX, int spriteCellCountY);

        bool isPlayerAttack();

        bool checkCollision(Rectangle entityHitbox);

        void draw();
        bool timedDraw(int action, int frames, int frameSpeed);

        float getPositionX();
        float getPositionY();
        void setPositionX(float newX);
        void setPositionY(float newY);
        //void setPosition(float newX, float newY);

        float getDirection();
        void setDirection(float newDirection);
};