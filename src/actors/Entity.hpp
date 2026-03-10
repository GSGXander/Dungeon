#pragma once
#include <raylib.h>
#include "src/core/animationHandler.hpp"

class Entity 
{
    protected:
        int health;
        float speed;
        Vector2 position;
        Rectangle hitbox;
        animationHandler animatedSprite;

    public:
        Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);

        void draw(int action);

        int gethealth();
        void sethealth(int new_health);
        float getspeed();
        void setspeed(int new_speed);

};
