#include "raylib.h"
#include "gui/button.hpp"
#include "gui/slider.hpp"
#include "gui/menu.hpp"
#include "actors/Entity.hpp"
#include "actors/Player.hpp"

int main()
{

////////////
const int screenWidth = 1280;
const int screenHeight = 720;
int gameMode = 1; // 0 = menu, 1 = game, 2 = transition
int currentMenu = 0;
bool endGame = false;
float transitionScreen = 0.0f;
float deltaTime;

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

////Rooms////

Rectangle tutorial_room[4] = {
    {0, 670.0f, 1280.0f, 50.0f}, 
    {0, 0, 1280.0f, 50.0f}, 
    {0, 50.0f, 50.0f, 620.0f},
    {1230.0f, 50.0f, 50.0f, 620.0f}};

////////////

Player player(0, 0, 0, {screenWidth/2, screenHeight/2}, "resources/playerMovementTest-Sheet.png", 2, 2);

////////////

SetTargetFPS(60);


while(!WindowShouldClose() && !endGame)
{
    BeginDrawing();
    deltaTime = GetFrameTime();

    if(gameMode != 1)
    {
        ClearBackground(GRAY);
    }
    else
    {
        ClearBackground(BLACK);
    }
    
    if (gameMode == 0) // Menu Mode
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
    else if (gameMode == 1) // Gameplay Mode
    {
        player.setVerticalSpeed(player.getVerticalSpeed() - (25.0f * deltaTime)); //Gravity 
        DrawText(TextFormat("VSPEED: %f", player.getVerticalSpeed()), 0,150,50,WHITE);
        player.movementKeyCheck(deltaTime);
        
        if(player.getHorizontalSpeed() != 0.0f)
        {
            player.setPositionX(player.getPositionX() + player.getHorizontalSpeed());
        }
        if(player.getVerticalSpeed() != 0.0f)
        {
            player.setPositionY(player.getPositionY() - player.getVerticalSpeed());
        }
        player.updateHithox();

        for(int i = 0; i < 4; i++)
        {
            DrawRectangleRec(tutorial_room[i], BLUE);
            player.playerCollisionCheck(tutorial_room[i]);
        }

        if(player.getHorizontalSpeed() != 0.0f)
        {
            player.draw(1);
        }
        else
        {
            player.draw(0,1);
        }
        
        DrawText(TextFormat("X Cord: %f", player.getPositionX()), 0,0,50,WHITE);
        DrawText(TextFormat("Y Cord: %f", player.getPositionY()), 0,50,50,WHITE);
        DrawText(TextFormat("Can Jump: %d", player.ableToJump()), 0,100,50,WHITE);

    }
    else // Transitional Mode
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
