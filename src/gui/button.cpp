#include "button.hpp"

button::button(Vector2 screenPosition, const char *textureLoc)
{
    position = screenPosition;
    buttonTexture = LoadTexture(textureLoc);
}

bool button::isPressed(Vector2 cursorLocation, bool isMousePressed)
{
    Rectangle buttonBounds;
    buttonBounds.x = position.x - buttonTexture.width/2;
    buttonBounds.y = position.y - buttonTexture.height/2;
    buttonBounds.height = buttonTexture.height;
    buttonBounds.width = buttonTexture.width;

    if(CheckCollisionPointRec(cursorLocation, buttonBounds) && isMousePressed)
    {
        return true;
    }
    return false;
}

void button::draw(const char *text)
{
    /*
    if(!isPressed)
    {
        DrawTextureV(buttonTexture, position, WHITE);
        DrawText(text, (position.x + buttonTexture.width/2), (position.y + buttonTexture.height/2), 20, BLACK);
    }
    else
    {
        DrawTextureV(buttonTexture, position, RED);
        DrawText(text, (position.x + buttonTexture.width/2), (position.y + buttonTexture.height/2), 20, BLACK);
    }
    */
    
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 20, 1);

    DrawTextureV(buttonTexture, {position.x - buttonTexture.width/2 , position.y - buttonTexture.height/2}, WHITE);
    DrawText(text, position.x - textSize.x/2, position.y - textSize.y/2, 20, BLACK);
}