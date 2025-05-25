#pragma once
#include "common.h"

class Floor : public RectangleShape {
public:

    Floor();
    void activate();
    bool isActivated() const;
    bool isHidden() const;
    void setHidden(bool hidden);
    void setPosition(float x, float y);
    FloatRect getGlobalBounds() const;

private:
    bool activated;
    bool ishidden;
};