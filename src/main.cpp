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

InitWindow(screenWidth, screenHeight, "Dungeon");

/////Menus/////
button *currentMenu;

button mainMenu[4] = {{{screenWidth/2 - 250.0f,screenHeight/2 + 150.0f}, "Start", "resources/gui/button_Resize.png"},
{{screenWidth/2,screenHeight/2 + 150.0f}, "Options", "resources/gui/button_Resize.png"},
{{screenWidth/2 + 250.0f,screenHeight/2 + 150.0f}, "Quit", "resources/gui/button_Resize.png"},
{{screenWidth - 200.0f, screenHeight - 100.0f}, "Achievements", "resources/gui/button_Resize.png"}};

////////////

//Player player(0, 0, 0, {screenWidth/2, screenHeight/2}, "resources/movementTest-Sheet.png", 2, 1);
//button testButton({screenWidth/2, screenHeight/2}, "resources/gui/button_Resize.png");
//slider testSlider({screenWidth/2, (screenHeight/2) + 200.0f}, "resources/gui/slider.png", "resources/gui/knob.png", 50);

////////////

SetTargetFPS(60);
currentMenu = mainMenu;

while(!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(GRAY);

    for(int i = 0; i < 4; i++)
    {
        (currentMenu + i)->draw();
    }

    EndDrawing();
}
CloseWindow();
}