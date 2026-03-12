#include "raylib.h"
#include "gui/button.hpp"
#include "gui/slider.hpp"
#include "gui/menu.hpp"
#include "actors/Entity.hpp"
#include "actors/Player.hpp"

int main()
{

////////////
const int screenWidth = 1920;
const int screenHeight = 1080;
int gameMode = 0; // 0 = menu, 1 = game, 2 = transition
int currentMenu = 0;
bool endGame = false;
float transitionScreen = 0.0f;

////Methods/////

void transition(float opacity);

////////////
InitWindow(screenWidth, screenHeight, "Dungeon");

/////Menus/////
std::vector<button> mainButtons = {
{{screenWidth/2 - 250.0f,screenHeight/2 + 150.0f}, "Start", "resources/gui/button_Resize.png"},
{{screenWidth/2,screenHeight/2 + 150.0f}, "Options", "resources/gui/button_Resize.png"},
{{screenWidth/2 + 250.0f,screenHeight/2 + 150.0f}, "Quit", "resources/gui/button_Resize.png"},
{{screenWidth - 200.0f, screenHeight - 100.0f}, "resources/gui/achievement_button.png"}};

std::vector<slider> optionsSliders =  {
{{screenWidth/2, (screenHeight/2) - 200.0f}, "resources/gui/slider.png", "resources/gui/knob.png", "Master Volume", 50},
{{screenWidth/2, (screenHeight/2)}, "resources/gui/slider.png", "resources/gui/knob.png", "Music Volume", 50},
{{screenWidth/2, (screenHeight/2) + 200.0f}, "resources/gui/slider.png", "resources/gui/knob.png", "Effects Volume", 50}};

std::vector<button> optionsButtons = {
{{screenWidth/4 , screenHeight/2 + 300.0f}, "Back", "resources/gui/button_Resize.png"}};

menu menuManager[3] = {{mainButtons}, {{optionsButtons},{optionsSliders}}, {optionsButtons}};

////Textures///
Texture2D logo = LoadTexture("resources/Default.png");


////////////

SetTargetFPS(60);


while(!WindowShouldClose() && !endGame)
{
    BeginDrawing();
    ClearBackground(GRAY);

    if (gameMode == 0)
    {
        switch (currentMenu)
        {
        case 0:     //Main Menu
            menuManager[0].draw();
            DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 200.0f, WHITE);
            switch (menuManager[0].isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            {
                case 0:         // Start button
                    gameMode = 2;
                    break;

                case 1:         // Options Button
                    currentMenu = 1;
                    break;

                case 2:         // Exit Button
                    endGame = true;
                    break;

                case 3:         // Achievements Button
                    currentMenu = 2;
                    break;

                default:
                break;
            }            
            break;
        
        case 1:     //Options Menu
            DrawRectangle(screenWidth/2 - (screenWidth/2 + screenWidth/4)/2, 
                screenHeight/2 - (screenHeight/2 + screenHeight/4)/2, 
                screenWidth/2 + screenWidth/4, 
                screenHeight/2 + screenHeight/4, 
                ORANGE);
            DrawText("Options", screenWidth/2 - MeasureText("Options", 30)/2, screenHeight/2 - 300.0f, 30, BLACK);
            menuManager[1].draw();
            switch (menuManager[1].isPressed(GetMousePosition(), IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
            {
                case 0:
                    break;

                case 1:
                    break;

                case 2:
                    break;

                case 3:         // Back Button
                    currentMenu = 0;
                    break;

                default:
                break;
            }
            break;

        case 2:     //Achievements Menu
            DrawRectangle(screenWidth/2 - (screenWidth/2 + screenWidth/4)/2, 
                screenHeight/2 - (screenHeight/2 + screenHeight/4)/2, 
                screenWidth/2 + screenWidth/4, 
                screenHeight/2 + screenHeight/4, 
                ORANGE);
            DrawText("Achievements", screenWidth/2 - MeasureText("Achievements", 30)/2, screenHeight/2 - 300.0f, 30, BLACK);
            menuManager[2].draw();
            if(menuManager[2].isPressed(GetMousePosition(), IsMouseButtonDown(MOUSE_BUTTON_LEFT)) == 0)
            {
                currentMenu = 0;
            }
            break;
            
        default:
            currentMenu = 0;
            break;
        }
    }
    else if (gameMode == 1)
    {
        ClearBackground(BLACK);
        DrawText("Insert game here", screenWidth/2 - MeasureText("Insert game here", 50)/2, screenHeight/2, 50, RED);
    }
    else
    {
        menuManager[currentMenu].draw();
        DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 200.0f, WHITE);
        transition(transitionScreen);
        transitionScreen = transitionScreen + 1.0f/30.0f;
        if(transitionScreen >= 1.3f)
        {
            gameMode = 1;
            transitionScreen = 0.0f;
        }
    }
    
    EndDrawing();
}
CloseWindow();
}

void transition(float opacity)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, opacity));
}