#pragma once
#include <raylib.h>
#include <vector>
#include "button.hpp"
#include "slider.hpp"

class menu
{
    private:
        std::vector<button> buttons;
        std::vector<slider> sliders;

    public:
        menu(std::vector<button> buttonList, std::vector<slider> sliderList);
        menu(std::vector<button> buttonList);

        int isPressed(Vector2 cursorLocation, bool isMousePressed);

        int getSliderValue(int Index);
        void setSliderValue(int Index, int val);

        void draw();
};