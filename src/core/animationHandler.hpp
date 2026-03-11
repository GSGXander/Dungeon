#pragma once
#include <raylib.h>

class animationHandler
{
    private: 
        int spriteCount;                //sprite # in the row
        float spriteX;                  //sprite left bound
        float spriteY;                  //sprite top bound
        int frameSpeed;                 //how long it takes to go to the next frame
        int frameCounter;               //current fps frame

        int cellXMax;
        float cellSizeX;                //Size of each cell horizontally (image size / number of horizontal cells)
        float cellSizeY;                //Size of each cell vertically(image size / number of vertical cells)
        Texture2D spriteSheet; 
    
    public:
        animationHandler(int cellCountX, int cellCountY, const char *sheetLocation);

        void playAnimation(int action);

        void playAnimation(int action, int speed);

        float getCellWidth();
        
        float getCellHeight();

        float getSpriteX();

        float getSpriteY();
        
        Texture2D getSpriteSheet();
};