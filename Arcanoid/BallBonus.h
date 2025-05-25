#pragma once
#include "Bonus.h"
#include "Ball.h"

class BallBonus : public Bonus {
public:
    BallBonus(float x, float y, BonusType type) : Bonus(x, y, type) {}
    virtual void applyToBall(Ball& ball) {};
};

class StickyBallBonus : public BallBonus {
public:
    StickyBallBonus(float x, float y);
    void applyToBall(Ball& ball) override;
};

class BallSpeedUpBonus : public BallBonus {
public:
    BallSpeedUpBonus(float x, float y);
    void applyToBall(Ball& ball) override;
};

class BallSpeedDownBonus : public BallBonus {
public:
    BallSpeedDownBonus(float x, float y);
    void applyToBall(Ball& ball) override;
};

class RandomTrajectoryBonus : public BallBonus {
public:
    RandomTrajectoryBonus(float x, float y);
    void applyToBall(Ball& ball) override;
};