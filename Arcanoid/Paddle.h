#pragma once
#include "common.h"

class Paddle : public RectangleShape {
public:
    Paddle();
    void update(float dt, bool moveLeft, bool moveRight);
    void setPosition(float x, float y);
    void setSize(Vector2f size);
    void increaseSize(float factor);
    void decreaseSize(float factor);

private:
    float speed;
    float width;
    float height;
};