#include "raylib.h"
#include "gui/button.hpp"
#include "gui/slider.hpp"
#include "actors/Entity.hpp"
#include "actors/Player.hpp"

int main()
{

////////////
const int screenWidth = 1920;
const int screenHeight = 1080;
////////////

////////////

InitWindow(screenWidth, screenHeight, "Dungeon");

Player player(0, 0, 0, {screenWidth/2, screenHeight/2}, "resources/movementTest-Sheet.png", 2, 1);
button testButton({screenWidth/2, screenHeight/2}, "resources/gui/button.png");
slider testSlider({screenWidth/2, (screenHeight/2) + 200.0f}, "resources/gui/slider.png", "resources/gui/knob.png", 50);

SetTargetFPS(60);

while(!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(GRAY);
    
    player.draw(0);
    testButton.draw("Hi!");
    testSlider.draw("Volume", testSlider.getValue());

    //DrawText("Hi.", screenWidth/2, screenHeight/2, 10, RED);

    if(testButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        ClearBackground(DARKGRAY);
    }

    if(testSlider.isPressed(GetMousePosition(), IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
    {
        
    }

    EndDrawing();
}
CloseWindow();
}
