#include "Dragon.hpp"

Dragon::Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY)
    : Entity(50, 10, pos, sheetLocation, spriteCellCountX, spriteCellCountY, 1.0f)
{
    phase = 0;

    frameTracker = 0;
    attackTimer = 2;
    movementTimer = 6;
    timerModifier = 1;
    currentLoc = 0;
    canAttack = false;
    canMove = false;
    invc = false;
}

Dragon::Dragon(Vector2 pos, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY, float spriteResize)
    : Entity(50, 10, pos, sheetLocation, spriteCellCountX, spriteCellCountY, spriteResize)
{
    phase = 0;

    frameTracker = 0;
    attackTimer = 2;
    movementTimer = 6;
    timerModifier = 1;
    currentLoc = 0;
    canAttack = false;
    canMove = false;
    invc = false;
}

void Dragon::setPhase(int xPhase)
{
    phase = xPhase;
}

int Dragon::getPhase()
{
    return phase;
}

void Dragon::timerAdvance()
{
    frameTracker++;
    if(frameTracker >= 60/timerModifier)
    {
        frameTracker = 0;
        movementTimer--;
        attackTimer--;
        if(attackTimer <= 0)
        {
            canAttack = true;
            attackTimer = 2;
        }
        else if (movementTimer <= 0)
        {
            canMove = true;
            movementTimer = 5;
        }
        
    }
}

void Dragon::setMaxHealth(int new_mHp)
{
    maxHealth = new_mHp;
}

int Dragon::getMaxHealth()
{
    return maxHealth;
}

int Dragon::getAttackTimer()
{
    return attackTimer;
}

int Dragon::getMovementTimer()
{
    return movementTimer;
}

int Dragon::getFrameTracker()
{
    return frameTracker;
}

bool Dragon::getCanAttack()
{
    return canAttack;
}

bool Dragon::getCanMove()
{
    return canMove; 
}

void Dragon::setCanAttack(bool foo)
{
    canAttack = foo;
}

void Dragon::setCanMove(bool foo)
{
    canMove = foo;
}

bool Dragon::isInvc()
{
    return invc;
}

void Dragon::setInvc(bool boo)
{
    invc = boo;
}
