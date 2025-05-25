#include "Floor.h"

Floor::Floor() {
    setSize({ FLOOR_WIDTH, FLOOR_HEIGHT });
    setPosition(0, WINDOW_HEIGHT - FLOOR_HEIGHT);
    setFillColor(Color::Cyan);
    activated = false;
    ishidden = true;
}

void Floor::activate() {
    activated = true;
    ishidden = false;
}

bool Floor:: isActivated() const {
    return activated;
}

bool Floor:: isHidden() const {
    return ishidden;
}

void Floor:: setHidden(bool hidden) {
    ishidden = hidden;
}

void Floor:: setPosition(float x, float y) {
    RectangleShape::setPosition(x, y);
}

FloatRect Floor:: getGlobalBounds() const { 
    return RectangleShape::getGlobalBounds(); 
}
