#pragma once
#include <raylib.h>
#include "src/core/animationHandler.hpp"

class Entity 
{
    protected:
        int health;
        float speed;
        float horizontalSpeed;
        float verticalSpeed;
        float direction;
        Vector2 position;
        Rectangle hitbox;
        animationHandler animatedSprite;
        float spriteScale;

    public:
        Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);
        Entity(int hp, float spd, Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY, float resizeMultiplier);

        void draw(int action);
        void draw(int action, int frameCount);
        void draw(int action, int frameCount, int speed);
        bool drawOnce(int action, int frameCount, int speed);
        bool drawEX(int action, int frameCount, int speed, Color tint, bool playOnce);

        int gethealth();
        void sethealth(int new_health);
        float getspeed();
        void setspeed(int new_speed);
        float getVerticalSpeed();
        void setVerticalSpeed(float new_speed);
        float getHorizontalSpeed();
        void setHorizontalSpeed(float new_speed);
        float getDirection();
        void setDirection(float newDirection);
        float getSpriteScale();
        void setSpriteScale(float new_scale);

        Rectangle getHitbox();
        void updateHithox();

        float getPositionX();
        float getPositionY();
        void setPositionX(int newX);
        void setPositionY(int newY);
};
