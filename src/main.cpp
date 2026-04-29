#include "raylib.h"
#include "gui/button.hpp"
#include "gui/slider.hpp"
#include "gui/menu.hpp"
#include "actors/Entity.hpp"
#include "actors/Player.hpp"
#include "obj/hazard.hpp"
#include "actors/Dragon.hpp"
#include "core/achievement.hpp"
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
float dragonInvcTimer;
json saveData;

////Methods/////

void transition(float opacity);
void gameStartState(Player *user, Dragon *drag);
void playerDataSave(Player *user);
void volumeDataSave(int masterVolume, int musicVolume, int effectsVolume);
void achievementDataSave(int index, bool setUnlocked);
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

////Achievements////
achievement achievementList[3] = {
    {"Youch", "Die for the first time.", "resources/hazards/testDanger.png"},
    {"Unobtainable", "This one just kinda sits here.", "resources/hazards/testDanger.png"},
    {"Unobtainable 2", "This one ALSO just kinda sits here.", "resources/hazards/testDanger.png"}};
////Rooms////

Rectangle tutorial_room[5] = {
    {0, 670.0f, 1310.0f, 50.0f},        //floor
    {0, 0, 1280.0f, 50.0f},             //ceiling
    {0, 50.0f, 50.0f, 620.0f},          //left wall
    {1230.0f, 50.0f, 50.0f, 470.0f},    //right wall
    {615.0f, 520.0f, 50.0f, 150.0f}};   //barrier
Rectangle interlude_room[5] = {
    {0, 50.0f, 50.0f, 470.0f},          //left wall
    {1230.0f, 50.0f, 50.0f, 620.0f},    //right wall
    {0, 0, 1280.0f, 50.0f},             //ceiling
    {-20, 670.0f, 460.0f, 50.0f},       //left floor
    {840.0f, 670.0f, 440.0f, 50.0f}};   //right floor
Rectangle dragon_room[5] = {
    {0, 50.0f, 50.0f, 620.0f},          //left wall
    {1230.0f, 50.0f, 50.0f, 620.0f},    //right wall
    {0, 670.0f, 1280.0f, 50.0f},        //floor
    {0, 0.0f, 440.0f, 50.0f},           //left ceiling
    {840.0f, 0.0f, 440.0f, 50.0f}};     //right ceiling

Rectangle *currentRoom = tutorial_room;
int currentRoomSize = 5;
int roomId = 0;

////Hazards////

hazard playerAttack({-100,-100}, "resources/slash-Sheet.png", true, true, 5, 1);
hazard testHazard({928.0f, 670.0f}, "resources/hazards/testDanger.png", false, true, 1, 1);
hazard *hazardList[10];
for(int i = 0; i < 10; i++)
{
    hazardList[i] = new hazard({-200.0f, -200.0f}, "resources/hazards/fireball-Sheet.png", false, false, 2, 1);
}
int currentHazard = 0;

///////////////


Player player(0, 0, 0, {150, 670.0f}, "resources/playerMovementTest-Sheet.png", 2, 2);
Dragon dragon({980.0f, 670.0f}, "resources/dragonAA223.png", 1, 1);
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
    for(int i = 0; i < 3; i++)
    {
        achievementList[i].setUnlocked(saveData["achievements"][i]["unlocked"]);
    }

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
                    gameStartState(&player, &dragon);
                    roomId = 0;
                    currentRoom = tutorial_room;
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
            for(int i = 0; i < 3; i++)
            {
                if(achievementList[i].isUnlocked())
                {
                    DrawRectangle(screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f + ((screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f))*(i%2),
                    screenHeight/2 - (screenHeight/2 + screenHeight/4)/2 + 10.0f + (65.0f * (i/2)),
                    (screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f),
                    60.0f,
                    GREEN);
                }
                else
                {
                    DrawRectangle(screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f + ((screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f))*(i%2),
                    screenHeight/2 - (screenHeight/2 + screenHeight/4)/2 + 10.0f + (65.0f * (i/2)),
                    (screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f),
                    60.0f,
                    RED);
                }
                DrawTexture(achievementList[i].getIcon(), screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 13.0f + ((screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f))*(i%2),
                screenHeight/2 - (screenHeight/2 + screenHeight/4)/2 + 13.0f + (65.0f * (i/2)), WHITE);

                DrawText(achievementList[i].getName().c_str(), screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 73.0f + ((screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f))*(i%2),
                screenHeight/2 - (screenHeight/2 + screenHeight/4)/2 + 13.0f + (65.0f * (i/2)), 20, BLACK);
                
                DrawText(achievementList[i].getDescription().c_str(), screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 73.0f + ((screenWidth/2 - 5.0f) - (screenWidth/2 - (screenWidth/2 + screenWidth/4)/2 + 10.0f))*(i%2),
                screenHeight/2 - (screenHeight/2 + screenHeight/4)/2 + 30.0f + (65.0f * (i/2)), 15, BLACK);
            }
            DrawText("Achievements", screenWidth/2 - MeasureText("Achievements", 30)/2, screenHeight/2 - 300.0f, 30, BLACK);
            menuManager[2].draw();
            if(menuManager[2].isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) == 0)
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
        
        ///////////////Player Frame Updates///////////////////////////
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

        if(player.getHorizontalSpeed() != 0.0f)
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

        if(player.gethealth() <= 0)
        {
            currentMenu = 4;
            gameMode = 0;
            player.setDeaths(player.getDeaths()+1);
            StopMusicStream(music);
            if(!achievementList[0].isUnlocked())
            {
                achievementList[0].setUnlocked(true);
                achievementDataSave(0, true);
            }
        }
        ///////////////////////////////////////////////////////////////////////////
        /////////////////Dragon Frame Updates//////////////////////////////////////

        if(dragon.getPhase() != 0)
        {
            dragon.timerAdvance();

            if(player.getPositionX() <= dragon.getPositionX())
            {
                dragon.setDirection(1.0f);
            }
            else
            {
                dragon.setDirection(-1.0f);
            }
            
            if(dragon.getCanAttack())
            {
                hazardList[currentHazard]->setPositionX(dragon.getPositionX()-40.0f*dragon.getDirection());
                hazardList[currentHazard]->setPositionY(dragon.getPositionY()-40.0f);
                hazardList[currentHazard]->setDirection(dragon.getDirection());
                hazardList[currentHazard]->setActiveTimer(0);
                
                float xDif = player.getPositionX() - hazardList[currentHazard]->getPositionX();
                float yDif = player.getPositionY() - hazardList[currentHazard]->getPositionY();

                hazardList[currentHazard]->setHorizontalSpeed(xDif/(float)sqrt(xDif*xDif + yDif*yDif)*-800.0f);
                hazardList[currentHazard]->setVerticalSpeed(yDif/(float)sqrt(xDif*xDif + yDif*yDif)*-800.0f);

                currentHazard++;
                if(currentHazard > 9)
                {
                    currentHazard = 0;
                }
                dragon.setCanAttack(false);
            }

            if(dragon.getCanMove() && !dragon.getCanAttack())
            {
                if(dragon.getPositionX() >= 640.0f)
                {
                    dragon.setPositionX(300.0f);
                }
                else
                {
                    dragon.setPositionX(980.0f);
                }
                dragon.setCanMove(false);
                dragon.updateHithox();
            }

            dragon.draw(0);

            if(dragonInvcTimer > 0.0f)
            {
                dragonInvcTimer -= 1.0f/60.0f;
                if(dragonInvcTimer <= 0.0f)
                {
                    dragon.setInvc(false);
                }
            }

            if(!player.ableToAttack() && playerAttack.checkCollision(dragon.getHitbox()) && !dragon.isInvc())
            {
                dragon.sethealth(dragon.gethealth()-1);
                dragon.setInvc(true);
                dragonInvcTimer = 1.0f;
            }

        }
        /////////PLAYER ATTACK///////////// (Down here cause of draw order)
        if(!player.ableToAttack())
        {
            playerAttack.setDirection(player.getAttackDirection());
            playerAttack.setPositionX(player.getAttackLocation().x - 80.0f*playerAttack.getDirection());
            playerAttack.setPositionY(player.getAttackLocation().y);
            if(!playerAttack.timedDraw(0,4,15))
            {
                player.setCanAttack(true);
            }
        }
        ///////////////////////////////////////////////////////////////////////////
        ////////////////////////////Hazard Frame Update////////////////////////////
        for(int i = 0; i < 10; i++)
        {
           if(hazardList[i]->getPositionX() >= 0.0f)
           {
                hazardList[i]->setPositionX(hazardList[i]->getPositionX()-hazardList[i]->getHorizontalSpeed()*deltaTime);
                hazardList[i]->setPositionY(hazardList[i]->getPositionY()-hazardList[i]->getVerticalSpeed()*deltaTime);
                hazardList[i]->draw();

                if(hazardList[i]->checkCollision(player.getHitbox()) && !player.isInvc())
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
                hazardList[i]->hazardRoomCollisionCheck(currentRoom, currentRoomSize);
                if(!hazardList[i]->getPersistence())
                {
                    hazardList[i]->setActiveTimer(hazardList[i]->getActiveTimer() + 1);
                    if(hazardList[i]->getActiveTimer()/60 >= 8)
                    {
                        hazardList[i]->setHorizontalSpeed(0.0f);
                        hazardList[i]->setVerticalSpeed(0.0f);
                        hazardList[i]->setPositionX(-200.0f);
                        hazardList[i]->setPositionY(-200.0f);
                    }
                } 
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////
        /*testHazard.draw();
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
        }*/
        
        ///////////Hud////////////////
        DrawTexture(hudPlate, 10.0f, 10.0f, WHITE);
        DrawTexture(profile, 25.0f, 15.0f, WHITE);
        for(int i = 0; i < player.gethealth(); i++)
        {
            DrawRectangle(130.0f + (27.0f*i), 25.0f, 25.0f, 70.0f, GREEN);
        }
        if(dragon.getPhase() != 0)
        {
            int hlthDif = -(300*dragon.gethealth()/dragon.getMaxHealth())+300;
            DrawTexturePro(hudPlate, {0.0f, 0.0f, -500.0f, 100.0f}, {1270.0f, 10.0f, 500.0f, 100.0f}, {500.0f, 0.0f}, 0.0f, WHITE);
            DrawRectangle(955, 25, 300 - hlthDif, 70, RED);
        }
        ///////////////////////////////
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
        switch(roomId) //new room trigger
        {
            case 0:
                if(player.getPositionX() >= 1290.0f)
                {
                    currentRoom = interlude_room;
                    roomId = 1;
                    currentRoomSize = 5;
                    player.setPositionX(10.0f);
                }
                break;
            case 1:
                if(player.getPositionX() <= 0.0f)
                {
                    currentRoom = tutorial_room;
                    roomId = 0;
                    currentRoomSize = 5;
                    player.setPositionX(1280.0f);
                }
                else if(player.getPositionY() >= 745.0f)
                {
                    currentRoom = dragon_room;
                    roomId = 2;
                    currentRoomSize = 5;
                    dragon.setPhase(1);
                    player.setPositionY(25.0f);
                    player.setPositionX(640.0f);
                }
                break;
            default:
                break;
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
            DrawText(TextFormat("Can Attack: %d", player.ableToAttack()), 0,350,50,WHITE);
            DrawText(TextFormat("Dragon MTimer: %i", dragon.getMovementTimer()), 0,400,50,WHITE);
            DrawText(TextFormat("Dragon FrameTrack: %i", dragon.getFrameTracker()), 0,450,50,WHITE);
            DrawText(TextFormat("Dragon Can Move: %d", dragon.getCanMove()), 0,500,50,WHITE);
            DrawText(TextFormat("Dragon Can Attack: %d", dragon.getCanAttack()), 0,550,50,WHITE);
            DrawText(TextFormat("Dragon Health: %i", dragon.gethealth()), 0,600,50,WHITE);
            DrawRectangleRec(player.getHitbox(), GREEN);
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

void gameStartState(Player *user, Dragon *drag)
{
    user->setPositionX(150.0f);
    user->setPositionY(670.0f);
    user->setInvc(false);
    user->setCanMove(true);
    user->sethealth(3+user->getHlthUpgrade());
    user->setspeed(user->getspeed()+user->getSpdUpgrade());
    user->setVerticalSpeed(0.0f);

    drag->setCanAttack(false);
    drag->setCanMove(false);
    drag->setPhase(0);
    drag->sethealth(5);
    drag->setMaxHealth(drag->gethealth());
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

void achievementDataSave(int index, bool setUnlocked)
{
    std::ifstream file("saveData.json");
    json data;

    if(file.is_open())
    {
        file >> data;
        file.close();

        data["achievements"][index]["unlocked"] = setUnlocked;

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
    data["achievements"] = json::array({{{"id", 0}, {"unlocked", false}}, {{"id", 1}, {"unlocked", false}}, {{"id", 2}, {"unlocked", false}}});

    std::ofstream file("saveData.json");
    file << data.dump(4);
}