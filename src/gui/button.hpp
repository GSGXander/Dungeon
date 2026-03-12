#pragma once
#include <raylib.h>
#include <string>

class button
{
    private:
        Vector2 position;
        Texture2D buttonTexture;
        std::string text;
    
    public:
        button(Vector2 screenPosition, std::string buttonText, const char *textureLoc);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        void draw();
};