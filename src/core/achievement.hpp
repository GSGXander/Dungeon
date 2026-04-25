#pragma once
#include <raylib.h>
#include <string>

class achievement
{
    private:
        std::string description;
        std::string name;
        bool unlocked;
        Texture2D icon;
        
    public:
        achievement(std::string achName, std::string achDesc, const char *textureLoc);

        std::string getDescription();
        std::string getName();
        bool isUnlocked();
        void setUnlocked(bool lock);
        Texture2D getIcon();
};