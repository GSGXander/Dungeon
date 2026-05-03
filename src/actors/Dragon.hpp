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
        int maxHealth;

        bool canAttack;
        bool canMove;
        bool invc;

        int currentLoc;
        Vector2 movementLocations[];

    public:
        Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);
        Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY, float spriteResize);

        void setMaxHealth(int new_mHp);
        int getMaxHealth();

        void setPhase(int xPhase);

        int getPhase();

        void timerAdvance();

        int getAttackTimer();

        int getMovementTimer();
        
        int getFrameTracker();

        bool isInvc();
        void setInvc(bool boo);

        bool getCanMove();
        bool getCanAttack();
        void setCanMove(bool foo);
        void setCanAttack(bool foo);
};
