#pragma once
#include <raylib.h>
#include "src/core/animationHandler.hpp"

class Entity 
{
    protected:
        int health;
        float speed;
        float verticalSpeed;
        Vector2 position;
        Rectangle hitbox;
        animationHandler animatedSprite;

    public:
        Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);

        void draw(int action);

        void draw(int action, int frameCount);

        int gethealth();
        void sethealth(int new_health);
        float getspeed();
        void setspeed(int new_speed);

        void updateHithox();

        float getPositionX();
        float getPositionY();
        void setPositionX(int newX);
        void setPositionY(int newY);
};
