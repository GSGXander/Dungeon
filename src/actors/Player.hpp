#pragma once
#include <raylib.h>
#include "Entity.hpp"

class Player : public Entity
{
    private:
        int deathCounter;
        float spdUpgrade;
        int hlthUpgrade;
        bool invc;
        bool canMove;
        bool canAttack;
        bool canJump;

    public:
        Player(int dCounter, float sUpgrade, int hUpgrade, Vector2 position, const char *sheetLocation, int spriteCellCountX, int spriteCellCountY);
            
        int getDeaths();
        void setDeaths(int newDeath);
    
        bool isInvc();
        void setInvc(bool boo);

        bool ableToMove();
        void setCanMove(bool boo);
    
        bool ableToAttack();
        void setCanAttack(bool boo);
    
        bool ableToJump();
        void setCanJump(bool boo);
};