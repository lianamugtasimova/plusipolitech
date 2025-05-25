#pragma once
#include "common.h"
#include "Paddle.h"
#include "Floor.h"

enum class BonusType {
    PADDLE_SIZE_INCREASE,
    PADDLE_SIZE_DECREASE,
    BALL_SPEED_UP,
    BALL_SPEED_DOWN,
    STICKY_BALL,
    ONE_TIME_FLOOR,
    RANDOM_TRAJECTORY
};

class Bonus : public RectangleShape {
public:
    Bonus(float x, float y, BonusType type);
    virtual ~Bonus() {}
    void update(float dt);
    BonusType getType() const;
    void setPosition(float x, float y);
private:
    BonusType type;
    Vector2f velocity;
};