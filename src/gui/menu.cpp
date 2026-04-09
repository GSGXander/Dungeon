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
        if(Slider.isPressed(cursorLocation, isMousePressed))
        {
            return buttonId;
        }
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

int menu::getSliderValue(int Index)
{
    return sliders[Index].getValue();
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