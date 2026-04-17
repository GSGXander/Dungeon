#include "raylib.h"
#include "gui/button.hpp"
#include "gui/slider.hpp"
#include "gui/menu.hpp"
#include "actors/Entity.hpp"
#include "actors/Player.hpp"
#include "obj/hazard.hpp"
#include <src/nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main()
{

////////////
const int screenWidth = 1280;
const int screenHeight = 720;
int gameMode = 0; // 0 = menu, 1 = game, 2 = transition
int currentMenu = 0;
bool endGame = false;
bool debug = false;
float transitionScreen = 0.0f;
float deltaTime;
float playerInvcTimer;
json saveData;

////Methods/////

void transition(float opacity);
void playerStartState(Player *user);
void playerDataSave(Player *user);
void volumeDataSave(int masterVolume, int musicVolume, int effectsVolume);
void createDefaultSave();

////////////
InitWindow(screenWidth, screenHeight, "Dungeon");
InitAudioDevice();
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

std::vector<button> pauseButtons = {
{{screenWidth/2, screenHeight/2 - 100.0f}, "Resume", "resources/gui/button_Resize.png"},
{{screenWidth/2, screenHeight/2 + 100.0f}, "Quit", "resources/gui/button_Resize.png"}};

std::vector<button> gameOverUpgrade = {
{{screenWidth/2 - 250.0f, screenHeight/2 + 200.0f}, "resources/gui/plusButton.png"},
{{screenWidth/2 + 250.0f, screenHeight/2 + 200.0f}, "resources/gui/plusButton.png"}};

menu menuManager[5] = {{mainButtons}, {{optionsButtons},{optionsSliders}}, {optionsButtons}, {pauseButtons}, {gameOverUpgrade}};

////Textures///
Texture2D logo = LoadTexture("resources/Default.png");
Texture2D hudPlate = LoadTexture("resources/gui/hudPlate.png");
Texture2D profile = LoadTexture("resources/gui/knightProfile.png");

////Rooms////

Rectangle tutorial_room[5] = {
    {0, 670.0f, 1280.0f, 50.0f},        //floor
    {0, 0, 1280.0f, 50.0f},             //ceiling
    {0, 50.0f, 50.0f, 620.0f},          //left wall
    {1230.0f, 50.0f, 50.0f, 620.0f},    //right wall
    {615.0f, 520.0f, 50.0f, 150.0f}};   //barrier
Rectangle *currentRoom = tutorial_room;
int currentRoomSize = 5;

////Hazards////

hazard testHazard({928.0f, 670.0f}, "resources/hazards/testDanger.png", false, true, 1, 1);

///////////////


Player player(0, 0, 0, {150, 670.0f}, "resources/playerMovementTest-Sheet.png", 2, 2);
Music music = LoadMusicStream("resources/music/hazy_maze_cave.mp3");
music.looping = true;
SetMusicVolume(music, (float)(optionsSliders[1].getValue())/100.0f);

////////////

SetTargetFPS(60);

std::ifstream inFile("saveData.json");
if(inFile.is_open())
{
    inFile >> saveData;

    player.setDeaths(saveData["player"]["deaths"]);
    player.setHlthUpgrade(saveData["player"]["healthBonus"]);
    player.setSpdUpgrade(saveData["player"]["speedBonus"]);
    menuManager[1].setSliderValue(0, saveData["settings"]["masterVolume"]);
    menuManager[1].setSliderValue(1, saveData["settings"]["musicVolume"]);
    menuManager[1].setSliderValue(2, saveData["settings"]["effectsVolume"]);

    inFile.close();
}
else
{
    createDefaultSave();
}

while(!endGame)
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
                    playerStartState(&player);
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
                    SetMusicVolume(music, (float)(menuManager[1].getSliderValue(1))/100.0f);
                    break;

                case 2:
                    break;

                case 3:         // Back Button
                    currentMenu = 0;
                    volumeDataSave(menuManager[1].getSliderValue(0), menuManager[1].getSliderValue(1), menuManager[1].getSliderValue(2));
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
        
        case 3:     //Pause Menu
            menuManager[3].draw();
            DrawText("Paused", screenWidth/2 - MeasureText("Paused", 30)/2, screenHeight/2 - 300.0f, 30, BLACK);
            switch(menuManager[3].isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            {
                case 0:
                    gameMode = 1;
                    break;
                case 1:
                    currentMenu = 0;
                    StopMusicStream(music);
                    break;
                default:
                    break;
            }
            if(IsKeyPressed(KEY_ESCAPE))
            {
                gameMode = 1;
            }
            break;
        
        case 4:     //Game Over Screen
            menuManager[4].draw();
            DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 50)/2, screenHeight/2 - 200.0f, 50, BLACK);
            DrawText("Upgrade Health", screenWidth/2 - 250.0f - MeasureText("Upgrade Health", 50)/2, screenHeight/2 + 100.0f, 50, BLACK);
            DrawText("Upgrade Speed", screenWidth/2 + 250.0f - MeasureText("Upgrade Speed", 50)/2, screenHeight/2 + 100.0f, 50, BLACK);
            DrawText(TextFormat("Death Count: %i", player.getDeaths()), 0,0,50,BLACK);
            DrawText(TextFormat("Current Health Upgrade: %i", player.getHlthUpgrade()), screenWidth/2 - 250.0f - MeasureText("Current Health Upgrade: ", 30)/2, screenHeight/2 + 300.0f, 30, BLACK);
            DrawText(TextFormat("Current Speed Upgrade: %i", (int)player.getSpdUpgrade()/10), screenWidth/2 + 250.0f - MeasureText("Current Speed Upgrade: ", 30)/2, screenHeight/2 + 300.0f, 30, BLACK);
            switch(menuManager[4].isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            {
                case 0:
                    player.setHlthUpgrade(player.getHlthUpgrade() + 1);
                    currentMenu = 0;
                    playerDataSave(&player);
                    break;
                case 1:
                    player.setSpdUpgrade(player.getSpdUpgrade() + 10.0f);
                    currentMenu = 0;
                    playerDataSave(&player);
                    break;
                default:
                    break;
            }
            break;
            
        default:
            currentMenu = 0;
            break;
        }
    }
    else if (gameMode == 1) // Gameplay Mode
    {
        UpdateMusicStream(music);
        if(!IsMusicStreamPlaying(music))
        {
            PlayMusicStream(music);
        }

        player.setVerticalSpeed(player.getVerticalSpeed() - (25.0f * deltaTime)); //Gravity 
        if(player.ableToMove())
        {
            player.movementKeyCheck(deltaTime);
        }

        if(player.getHorizontalSpeed() != 0.0f)
        {
            player.setPositionX(player.getPositionX() + player.getHorizontalSpeed());
        }
        if(player.getVerticalSpeed() != 0.0f)
        {
            player.setPositionY(player.getPositionY() - player.getVerticalSpeed());
        }
        player.updateHithox();

        for(int i = 0; i < currentRoomSize; i++)
        {
            Rectangle *Rect = currentRoom + i;
            DrawRectangleRec(*Rect, BLUE);
        }
        player.playerCollisionCheck(currentRoom, currentRoomSize);

        if(player.getHorizontalSpeed() != 0.0f) //Player Movement Animations
        {
            player.draw(1);
        }
        else
        {
            player.draw(0,1);
        }

        if(playerInvcTimer > 0.0f)
        {
            playerInvcTimer -= 1.0f/60.0f;
            if(playerInvcTimer <= 0.0f)
            {
                player.setInvc(false);
            }
        }

        testHazard.draw();
        if(testHazard.checkCollision(player.getHitbox()) && !player.isInvc())
        {
            player.sethealth(player.gethealth()-1);
            player.setInvc(true);
            playerInvcTimer = 2.0f;
            player.setCanMove(false);
            
            player.setVerticalSpeed(500.0f * deltaTime);
            if(player.getPositionX() >= testHazard.getPositionX())
            {
                player.setHorizontalSpeed(150.0f * deltaTime);
            }
            else
            {
                player.setHorizontalSpeed(-150.0f * deltaTime);
            }
        }

        if(player.gethealth() <= 0)
        {
            currentMenu = 4;
            gameMode = 0;
            player.setDeaths(player.getDeaths()+1);
            StopMusicStream(music);
        }

        DrawTexture(hudPlate, 10.0f, 10.0f, WHITE);
        DrawTexture(profile, 25.0f, 15.0f, WHITE);
        for(int i = 0; i < player.gethealth(); i++)
        {
            DrawRectangle(130.0f + (27.0f*i), 25.0f, 25.0f, 70.0f, GREEN);
        }
        
        if(IsKeyPressed(KEY_GRAVE))
        {
            debug = !debug;
        }
        if(IsKeyPressed(KEY_ESCAPE))
        {
            currentMenu = 3;
            gameMode = 0;
            PauseMusicStream(music);
        }

        if(debug)
        {
            DrawText(TextFormat("X Cord: %f", player.getPositionX()), 0,0,50,WHITE);
            DrawText(TextFormat("Y Cord: %f", player.getPositionY()), 0,50,50,WHITE);
            DrawText(TextFormat("Can Jump: %d", player.ableToJump()), 0,100,50,WHITE);
            DrawText(TextFormat("VSPEED: %f", player.getVerticalSpeed()), 0,150,50,WHITE);
            DrawText(TextFormat("HSPEED: %f", player.getHorizontalSpeed()), 0,200,50,WHITE);
            DrawText(TextFormat("Direction: %f", player.getDirection()), 0,250,50,WHITE);
            DrawText(TextFormat("ITimer: %f", playerInvcTimer), 0,300,50,WHITE);
        }

    }
    else if(gameMode == 2)// Transitional Mode
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

void playerStartState(Player *user)
{
    user->setPositionX(150.0f);
    user->setPositionY(670.0f);
    user->setInvc(false);
    user->setCanMove(true);
    user->sethealth(3+user->getHlthUpgrade());
    user->setspeed(user->getspeed()+user->getSpdUpgrade());
}

void playerDataSave(Player *user)
{
    std::ifstream file("saveData.json");
    json data;

    if(file.is_open())
    {
        file >> data;
        file.close();

        data["player"]["deaths"] = user->getDeaths();
        data["player"]["healthBonus"] = user->getHlthUpgrade();
        data["player"]["speedBonus"] = user->getSpdUpgrade();

        std::ofstream outFile("saveData.json");
        outFile << data.dump(4);
        outFile.close();
    }
}

void volumeDataSave(int masterVolume, int musicVolume, int effectsVolume)
{
    std::ifstream file("saveData.json");
    json data;

    if(file.is_open())
    {
        file >> data;
        file.close();

        data["settings"]["masterVolume"] = masterVolume;
        data["settings"]["musicVolume"] = musicVolume;
        data["settings"]["effectsVolume"] = effectsVolume;

        std::ofstream outFile("saveData.json");
        outFile << data.dump(4);
        outFile.close();
    }
}

void createDefaultSave()
{
    json data;

    data["player"] = {{"deaths", 0}, {"healthBonus", 0}, {"speedBonus", 0}};
    data["settings"] = {{"masterVolume", 50}, {"musicVolume", 50}, {"effectsVolume", 50}};
    data["achievements"] = json::array({{{"id", 0}, {"unlocked", false}}, {{"id", 1}, {"unlocked", false}}});

    std::ofstream file("saveData.json");
    file << data.dump(4);
}
