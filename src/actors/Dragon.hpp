#pragma once
#include <raylib.h>
#include "Entity.hpp"

class Dragon : public Entity
{
    private:
        int phase;
        int attackTimer;
        int movementTimer;
        int timerModifier;
        int frameTracker;

        bool canAttack;
        bool canMove;
        
        int currentLoc;
        Vector2 movementLocations[];

    public:
        Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);

        void setPhase(int xPhase);

        int getPhase();

        void timerAdvance();

        int getAttackTimer();

        int getMovementTimer();
        
        int getFrameTracker();

        bool getCanMove();
        bool getCanAttack();
        void setCanMove(bool foo);
        void setCanAttack(bool foo);
};
