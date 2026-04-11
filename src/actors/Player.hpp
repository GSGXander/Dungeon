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
        
        void movementKeyCheck(float delta);
        void playerCollisionCheck(Rectangle *Rec, int roomSize);

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

        int getHlthUpgrade();
        void setHlthUpgrade(int new_hUpg);

        float getSpdUpgrade();
        void setSpdUpgrade(float new_sUpg);
};