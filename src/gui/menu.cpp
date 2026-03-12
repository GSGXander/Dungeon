#include "menu.hpp"

menu::menu(std::vector<button> buttonList, std::vector<slider> sliderList, std::vector<Texture2D> decalList)
    :buttons(buttonList), sliders(sliderList), decals(decalList)
{}

menu::menu(std::vector<button> buttonList, std::vector<Texture2D> decalList)
    :buttons(buttonList), decals(decalList)
{}


bool menu::isPressed(Vector2 cursorLocation, bool isMousePressed)
{
    for(int i = 0; i < sliders.size(); i++)
    {
        sliders[i].isPressed(cursorLocation, isMousePressed);
    }
    for(int i = 0; i < buttons.size(); i++)
    {
        buttons[i].isPressed(cursorLocation, isMousePressed);
    }
}

void menu::draw()
{
    for(int i = 0; i < sliders.size(); i++)
    {
        sliders[i].draw();
    }
    for(int i = 0; i < buttons.size(); i++)
    {
        buttons[i].draw();
    }
    for(int i = 0; i < decals.size(); i++)
    {
        
    }
}