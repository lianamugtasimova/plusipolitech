#include "Paddle.h"

Paddle::Paddle() : width(PADDLE_WIDTH), height(PADDLE_HEIGHT) {
    setSize({ width, height });
    setPosition(PADDLE_POX_X, PADDLE_POS_Y);
    setFillColor(Color::White);
    speed = PADDLE_SPEED;
}

void Paddle::update(float dt, bool moveLeft, bool moveRight) {
    if (moveLeft) {
        move(-speed * dt, 0);
        if (getPosition().x < 0) {
            setPosition(0, getPosition().y);
        }
    }
    if (moveRight) {
        move(speed * dt, 0);
        if (getPosition().x + getSize().x > WINDOW_WIDTH) {
            setPosition(WINDOW_WIDTH - getSize().x, getPosition().y);
        }
    }
}

void Paddle::setPosition(float x, float y) {
    RectangleShape::setPosition(x, y);
}

void Paddle::setSize(Vector2f size) {
    RectangleShape::setSize(size);
}

void Paddle::increaseSize(float factor) {
    float increased = width * factor;
    if (increased < PADDLE_MAX_WIDTH) {
        width = increased;
        setSize({ width, height });
        //setPosition(getPosition().x, getPosition().y);
    }
}

void Paddle:: decreaseSize(float factor) {
    float decreased = width * factor;
    if (decreased > PADDLE_MIN_WIDTH) {
        width = decreased;
        setSize({ width, height });
        //setPosition(getPosition().x, getPosition().y);
    }
}