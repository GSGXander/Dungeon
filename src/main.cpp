#include "raylib.h"
#include "button.hpp"

int main()
{

////////////
const int screenWidth = 1920;
const int screenHeight = 1080;
////////////

////////////

InitWindow(screenWidth, screenHeight, "Dungeon");

button testButton({screenWidth/2, screenHeight/2}, "resources/button/button.png");

SetTargetFPS(60);

while(!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(GRAY);
    
    testButton.draw("Hi!");
    //DrawText("Hi.", screenWidth/2, screenHeight/2, 10, RED);

    if(testButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        ClearBackground(RED);
    }

    EndDrawing();
}
CloseWindow();
}
