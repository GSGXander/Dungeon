#include "menu.hpp"

menu::menu(std::vector<button> buttonList, std::vector<slider> sliderList)
    :buttons(buttonList), sliders(sliderList)
{}

menu::menu(std::vector<button> buttonList)
    :buttons(buttonList)
{}


int menu::isPressed(Vector2 cursorLocation, bool isMousePressed)
{
    int buttonId = -1;
    for(auto& Slider : sliders)
    {
        buttonId++;
        Slider.isPressed(cursorLocation, isMousePressed);
    }
    for(auto& Button : buttons)
    {
        buttonId++;
        if(Button.isPressed(cursorLocation, isMousePressed))
        {
            return buttonId;
        }
    }
    return -5;
}

void menu::draw()
{
    for(auto& Slider : sliders)
    {
        Slider.draw();
    }
    for(auto& Button : buttons)
    {
        Button.draw();
    }
}