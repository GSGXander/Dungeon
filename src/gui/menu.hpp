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
        std::vector<Texture2D> decals;

    public:
        menu(std::vector<button> buttonList, std::vector<slider> sliderList, std::vector<Texture2D> decalList);
        menu(std::vector<button> buttonList, std::vector<Texture2D> decalList);

        bool isPressed(Vector2 cursorLocation, bool isMousePressed);

        void draw();
};