#pragma once
#include <raylib.h>
#include <string>

class slider
{
    private:
        Vector2 trackPos;
        float knobPos;
        Texture2D trackTexture;
        Texture2D knobTexture;
        std::string text;
        int value;
    
    public:
        slider(Vector2 position,  const char *trTexture, const char *knTexture, std::string buttonText,int val);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        void draw();

        int getValue();
        void setValue(int val);
};