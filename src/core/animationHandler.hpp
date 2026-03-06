#pragma once
#include <raylib.h>

class animationHandler
{
    private: 
        int spriteCount;                //sprite # in the row
        float spriteX;                  //sprite left bound
        float spriteY;                  //sprite top bound
        int frameSpeed;                 //how long it takes to go to the next frame

        float cellSizeX;                //Size of each cell (image size / number of horizontal cells)
        float cellSizeY;                //s
        Texture2D spriteSheet;
    
    public:
        animationHandler(float sprSizeX, float sprSizeY, const char *sheetLocation);

        
};