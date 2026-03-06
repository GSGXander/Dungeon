#pragma once
#include <raylib.h>

class button
{
    private:
        Vector2 position;
        Texture2D buttonTexture;
    
    public:
        button(Vector2 screenPosition, const char *textureLoc);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        void draw(const char *text);
};