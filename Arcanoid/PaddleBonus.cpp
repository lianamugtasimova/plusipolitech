#include "PaddleBonus.h"

PaddleSizeIncreaseBonus::PaddleSizeIncreaseBonus(float x, float y) 
    : PaddleBonus(x, y, BonusType::PADDLE_SIZE_INCREASE) {
    setFillColor(Color::Green);
}

void PaddleSizeIncreaseBonus:: applyToPaddle(Paddle& paddle)  {
    paddle.increaseSize(1.2f);
}

PaddleSizeDecreaseBonus::PaddleSizeDecreaseBonus(float x, float y) 
    : PaddleBonus(x, y, BonusType::PADDLE_SIZE_DECREASE) {
    setFillColor(Color::Red);
}

void PaddleSizeDecreaseBonus:: applyToPaddle(Paddle& paddle) {
    paddle.decreaseSize(0.8f);
}