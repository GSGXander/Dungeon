#include "slider.hpp"

slider::slider(Vector2 position,  const char *trTexture, const char *knTexture, int val)
{
    trackPos = position;
    trackTexture = LoadTexture(trTexture);
    knobTexture = LoadTexture(knTexture);
    value = val;
    
    float leftBound = trackPos.x - trackTexture.width/2;
    float rightBound = trackPos.x + trackTexture.width/2;
    knobPos = ((((float)val*(rightBound - leftBound))/100.0f)+leftBound) + 5.0f;
}

int slider::getValue()
{
    return value;
}

void slider::setValue(int val)
{
    value = val;
}

bool slider::isPressed(Vector2 cursorLocation, bool isMousePressed)
{
    Rectangle trackBounds{trackPos.x - trackTexture.width/2, trackPos.y - trackTexture.height/2, 
        static_cast<float>(trackTexture.width), static_cast<float>(trackTexture.height)};
    
    if(CheckCollisionPointRec(cursorLocation, trackBounds) && isMousePressed)
    {
        float leftBound = trackPos.x - trackTexture.width/2;
        float rightBound = trackPos.x + trackTexture.width/2;
        
        knobPos = cursorLocation.x - knobTexture.width/2;
        value = (int)((100.0f / (rightBound - leftBound)) * (knobPos - leftBound)) + 5.0f;
        return true;
    }
    return false;
}

void slider::draw(const char *text, int val)
{
    DrawTextureV(trackTexture, {trackPos.x - trackTexture.width/2, trackPos.y - trackTexture.height/2}, WHITE);
    DrawTextureV(knobTexture, {knobPos, trackPos.y - trackTexture.height/2}, WHITE);
    DrawText(TextFormat(text, "%i", val), trackPos.x - 5.0f, trackPos.y + 50.0f, 30, BLACK);
}
