#include "button.hpp"

button::button(Vector2 screenPosition, std::string buttonText, const char *textureLoc)
{
    position = screenPosition;
    buttonTexture = LoadTexture(textureLoc);
    text = buttonText;
    value = 0;
}

button::button(Vector2 screenPosition, const char *textureLoc)
{
    position = screenPosition;
    buttonTexture = LoadTexture(textureLoc);
    text = "";
    value = 0;
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

int button::isPressedVal(Vector2 cursorLocation, bool isMousePressed)
{
    Rectangle buttonBounds;
    buttonBounds.x = position.x - buttonTexture.width/2;
    buttonBounds.y = position.y - buttonTexture.height/2;
    buttonBounds.height = buttonTexture.height;
    buttonBounds.width = buttonTexture.width;

    if(CheckCollisionPointRec(cursorLocation, buttonBounds) && isMousePressed)
    {
        return value;
    }
    return -2;
}

int button::getValue()
{
    return value;
}

void button::draw()
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
    
    const char *buttonText = text.c_str();

    Vector2 textSize = MeasureTextEx(GetFontDefault(), buttonText, 20, 1);

    DrawTextureV(buttonTexture, {position.x - buttonTexture.width/2 , position.y - buttonTexture.height/2}, WHITE);
    DrawText(buttonText, position.x - textSize.x/2, position.y - textSize.y/2, 20, BLACK);
}