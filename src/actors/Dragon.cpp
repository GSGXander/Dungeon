#include "Dragon.hpp"

Dragon::Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY)
    : Entity(100, 10, pos, sheetLocation, spriteCellCountX, spriteCellCountY)
{
    phase = 1;

    frameTracker = 0;
    attackTimer = 2;
    movementTimer = 4;
    timerModifier = 1;
    currentLoc = 0;
    canAttack = false;
}

void Dragon::nextPhase()
{
    phase++;
}

void Dragon::timerAdvance()
{
    frameTracker++;
    if(frameTracker >= 60/timerModifier)
    {
        frameTracker = 0;
        movementTimer--;
        attackTimer--;
        if(attackTimer == 0)
        {
            canAttack = true;
            attackTimer = 5;
        }
        else if (movementTimer)
        {
            currentLoc++;
            position.x = movementLocations[currentLoc].x;
            position.y = movementLocations[currentLoc].y;
        }
        
    }
}