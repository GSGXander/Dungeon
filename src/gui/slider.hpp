#pragma once
#include <raylib.h>

class slider
{
    private:
        Vector2 trackPos;
        float knobPos;
        Texture2D trackTexture;
        Texture2D knobTexture;
        int value;
    
    public:
        slider(Vector2 position,  const char *trTexture, const char *knTexture, int val);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        void draw(const char *text, int val);

        int getValue();
        void setValue(int val);
};