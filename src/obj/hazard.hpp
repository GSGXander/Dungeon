#pragma once
#include <raylib.h>
#include "src/core/animationHandler.hpp"

class hazard
{
    private:
        Rectangle hitbox;
        Vector2 position;
        animationHandler animatedSprite;
        float horizontalSpeed;
        float verticalSpeed;
        bool playerAttack;
        bool isPersistent;
        float direction;
        int activeTimer;
    
    public:
        hazard(Vector2 pos, const char *sprite, bool plyAttack, bool persistent, int spriteCellCountX, int spriteCellCountY);

        bool isPlayerAttack();

        bool checkCollision(Rectangle entityHitbox);

        void draw();
        bool timedDraw(int action, int frames, int frameSpeed);
        void hazardRoomCollisionCheck(Rectangle *Rec, int roomSize);

        float getPositionX();
        float getPositionY();
        void setPositionX(float newX);
        void setPositionY(float newY);
        float getVerticalSpeed();
        void setVerticalSpeed(float new_speed);
        float getHorizontalSpeed();
        void setHorizontalSpeed(float new_speed);

        float getDirection();
        void setDirection(float newDirection);

        int getActiveTimer();
        void setActiveTimer(int new_timer);

        bool getPersistence();
};