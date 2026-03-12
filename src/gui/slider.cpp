#include "slider.hpp"

slider::slider(Vector2 position,  const char *trTexture, const char *knTexture, std::string buttonText, int val)
{
    trackPos = position;
    trackTexture = LoadTexture(trTexture);
    knobTexture = LoadTexture(knTexture);
    value = val;
    text = buttonText;
    
    float leftBound = trackPos.x - trackTexture.width/2;
    float rightBound = trackPos.x + trackTexture.width/2;
    knobPos = ((((float)val*(rightBound - leftBound))/100.0f)+leftBound) - 20.0f;
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
        float leftBound = trackPos.x - trackTexture.width/2 + 10.0f;
        float rightBound = trackPos.x + trackTexture.width/2 - 10.0f;
        
        knobPos = cursorLocation.x - knobTexture.width/2;
        value = (int)((100.0f / (rightBound - leftBound)) * (knobPos - leftBound)) + 5.0f;
        if(value > 100)
        {
            value = 100;
        }
        else if (value < 0)
        {
            value = 0;
        }
        
        return true;
    }
    return false;
}

void slider::draw()
{
    const char *buttonText = text.c_str();
    
    DrawTextureV(trackTexture, {trackPos.x - trackTexture.width/2, trackPos.y - trackTexture.height/2}, WHITE);
    DrawTextureV(knobTexture, {knobPos, trackPos.y - trackTexture.height/2}, WHITE);
    DrawText(TextFormat("%s: %i", buttonText, value), trackPos.x - (float)MeasureText(TextFormat("%s: %i", buttonText, value), 30)/2, trackPos.y + 50.0f, 30, BLACK);

    
}
