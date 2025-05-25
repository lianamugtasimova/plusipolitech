#include "Bonus.h"
#include "Paddle.h"

class PaddleBonus : public Bonus {
public:
    PaddleBonus(float x, float y, BonusType type) : Bonus(x, y, type) {}
    virtual void applyToPaddle(Paddle& paddle) {};
};

class PaddleSizeIncreaseBonus : public PaddleBonus {
public:
    PaddleSizeIncreaseBonus(float x, float y);
    void applyToPaddle(Paddle& paddle) override;
};

class PaddleSizeDecreaseBonus : public PaddleBonus {
public:
    PaddleSizeDecreaseBonus(float x, float y);
    void applyToPaddle(Paddle& paddle) override;
};

