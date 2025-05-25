#include "BallBonus.h"

StickyBallBonus::StickyBallBonus(float x, float y) :
    BallBonus(x, y, BonusType::STICKY_BALL) {
    setFillColor(Color::Cyan);
}

void StickyBallBonus::applyToBall(Ball& ball) {
    ball.setSticky();
}

BallSpeedUpBonus::BallSpeedUpBonus(float x, float y) :
    BallBonus(x, y, BonusType::BALL_SPEED_UP) {
    setFillColor(Color::Blue);
}

void BallSpeedUpBonus::applyToBall(Ball& ball) {
    ball.increaseSpeed(1.2f);
}

BallSpeedDownBonus::BallSpeedDownBonus(float x, float y) :
    BallBonus(x, y, BonusType::BALL_SPEED_DOWN) {
    setFillColor(Color::Magenta);
}

void BallSpeedDownBonus:: applyToBall(Ball& ball) {
    ball.decreaseSpeed(0.8f);
}

RandomTrajectoryBonus::RandomTrajectoryBonus(float x, float y) :
    BallBonus(x, y, BonusType::RANDOM_TRAJECTORY) {
    setFillColor(Color::White);
}

void RandomTrajectoryBonus::applyToBall(Ball& ball) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0); 

    ball.startRandomTrajectoryTimer(dis(gen));
}