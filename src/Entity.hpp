#pragma once
#include <raylib.h>

class Entity 
{
    protected:

        int health;
        int speed;
        Vector2 position;
        Texture2D spriteSheet;
        Rectangle hitbox;
    public:
        Entity(int hp, int spd, Vector2 pos, const char *sheetLocation);

        void draw(int frame, int action);

        int gethealth();
        void sethealth(int new_health);
        int getspeed();
        void setspeed(int new_speed);

};
