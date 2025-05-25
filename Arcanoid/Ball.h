#pragma once
#include "common.h"
#include "Paddle.h"
#include "Block.h"

class Ball : public CircleShape {
public:
    Ball();
    Vector2f velocity;
    void update(float dt);
    void setVelocity(Vector2f vel);
    Vector2f getVelocity() const;
    void stickToPaddle(Paddle& paddle);
    void releaseFromPaddle();
    bool isSticky() const { return sticky; }
    void setSticky();
    void setPosition(float x, float y);
    void reverseHorizontalVelocity();
    void reverseVerticalVelocity();
    void increaseSpeed(float factor);
    void decreaseSpeed(float factor);
    void setRandomTrajectory();
    void separateFromBlock(RectangleShape rect);
    void startRandomTrajectoryTimer(float delay);
private:
    bool sticky;
    bool onFloorHit = false;
    bool randomTrajectoryTimerActive = false;
    float randomTrajectoryTimer = 0.0f;
};
