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
        
        int currentLoc;
        Vector2 movementLocations[];

    public:
        Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);

        void nextPhase();

        void timerAdvance();
};
