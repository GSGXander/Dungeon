#pragma once
#include <raylib.h>

class Entity 
{
    protected:

        int health;
        int speed;
        Vector2 Position;
        
        Entity(int hp, int spd, Vector2 Pos);

        int gethealth();
        void sethealth(int new_health);
        int getspeed();
        void setspeed(int new_speed);

};
