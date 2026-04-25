#include "achievement.hpp"

achievement::achievement(std::string achName, std::string achDesc, const char *textureLoc)
{
    name = achName;
    description = achDesc;
    unlocked = false;
    icon = LoadTexture(textureLoc);
}

std::string achievement::getDescription()
{
    return description;
}

std::string achievement::getName()
{
    return name;
}

bool achievement::isUnlocked()
{
    return unlocked;
}

void achievement::setUnlocked(bool lock)
{
    unlocked = lock;
}

Texture2D achievement::getIcon()
{
    return icon;
}