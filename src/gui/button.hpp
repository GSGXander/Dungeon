#pragma once
#include <raylib.h>
#include <string>

class button
{
    private:
        Vector2 position;
        Texture2D buttonTexture;
        std::string text;
        int value;
    
    public:
        button(Vector2 screenPosition, std::string buttonText, const char *textureLoc);
        button(Vector2 screenPosition, const char *textureLoc);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        int isPressedVal(Vector2 cursorLocation, bool isMousePressed);

        int getValue();

        void draw();
};