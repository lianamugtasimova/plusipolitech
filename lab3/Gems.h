#pragma once
#include "common.h"
class Gem {
public:
    Gem(int color)
        : color(color), isActive(true) {}

    int getColor() const { return color; }
    bool isGemActive() const { return isActive; }

    void setColor(int newColor) { color = newColor; }
    void deactivate() { isActive = false; }
    int color;
    bool isActive;
};