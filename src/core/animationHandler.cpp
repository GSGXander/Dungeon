#include "animationHandler.hpp"

animationHandler::animationHandler(int cellCountX, int cellCountY, const char *sheetLocation)
{
    spriteSheet = LoadTexture(sheetLocation);
    
    cellXMax = cellCountX;

    cellSizeX = spriteSheet.width/(float)cellCountX;
    cellSizeY = spriteSheet.height/(float)cellCountY;
    frameSpeed = 8;
}

void animationHandler::playAnimation(int action)
{
    if(((float)action * cellSizeY) == spriteY)
    {
        frameCounter++;
        if(frameCounter >= (60/frameSpeed))
        {
            frameCounter = 0;
            spriteX += cellSizeX;
            if(spriteX > (float)cellXMax*cellSizeX)
            {
                spriteX = 0.0f;
            }
        }
    }
    else
    {
        spriteX = 0.0f;
        spriteY = (float)action * cellSizeY;
    }
}

void animationHandler::playAnimation(int action, int speed)
{
    if(((float)action * cellSizeY) == spriteY)
    {
        frameCounter++;
        if(frameCounter >= (60/speed))
        {
            frameCounter = 0;
            spriteX += cellSizeX;
            if(spriteX > (float)cellXMax-1*cellSizeX)
            {
                spriteX = 0.0f;
            }
        }
    }
    else
    {
        spriteX = 0.0f;
        spriteY = (float)action * cellSizeY;
    }
}

float animationHandler::getCellWidth()
{
    return cellSizeX;
}

float animationHandler::getCellHeight()
{
    return cellSizeY;
}

float animationHandler::getSpriteX()
{
    return spriteX;
}

float animationHandler::getSpriteY()
{
    return spriteY;
}

Texture2D animationHandler::getSpriteSheet()
{
    return spriteSheet;
}