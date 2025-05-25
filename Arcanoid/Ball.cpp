#include "Ball.h"

Ball::Ball() //: radius(BALL_RADIUS)
{
    setRadius(BALL_RADIUS);
    setPosition(BALL_POSX, BALL_POSY);
    setFillColor(Color::White);
    velocity = { BALL_VELOCITY_X, BALL_VELOCITY_Y };
    sticky = false;
}

void Ball::reverseHorizontalVelocity() {
    velocity.x = -velocity.x;
}

void Ball::reverseVerticalVelocity() {
    velocity.y = -velocity.y;
}

void Ball::update(float dt) {
    if (randomTrajectoryTimerActive) {
        randomTrajectoryTimer -= dt;
        if (randomTrajectoryTimer <= 0) {
            setRandomTrajectory();
            randomTrajectoryTimerActive = false;
        }
    }

    if (!sticky) {
        move(velocity * dt);

        if (getPosition().x < 0 || getPosition().x + getRadius() * 2 > WINDOW_WIDTH) {
            reverseHorizontalVelocity();
        }
        if (getPosition().y < 0) {
            reverseVerticalVelocity();
        }
    }
}

void Ball::setVelocity(Vector2f vel) {
    velocity = vel;
}

Vector2f Ball:: getVelocity() const {
    return velocity;
}

void Ball::stickToPaddle(Paddle& paddle) {
    sticky = true;
    setPosition(paddle.getPosition().x + paddle.getSize().x / 2 - getRadius(), paddle.getPosition().y - getRadius() * 2);
}

void Ball:: releaseFromPaddle() {
    sticky = false;
    velocity = { BALL_VELOCITY_X, -BALL_VELOCITY_Y }; 
}

void Ball:: setSticky() {
    sticky = true;
}

void Ball::setPosition(float x, float y) {
    CircleShape::setPosition(x, y);
}

void Ball::increaseSpeed(float factor) {
    Vector2f increased = velocity * factor;
    float speed = sqrt(increased.x * increased.x + increased.y * increased.y);
    if (speed < BALL_MAX_SPEED) {
        velocity = increased;
    }
}

void Ball::decreaseSpeed(float factor) {
    Vector2f decreased = velocity * factor;
    float speed = sqrt(decreased.x * decreased.x + decreased.y * decreased.y);
    if (speed > BALL_MIN_SPEED) {
        velocity = decreased;
    }
}

void Ball::setRandomTrajectory() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-1.0, 1.0);

    float currentSpeed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    float newX = static_cast<float>(dis(gen));
    float newY = static_cast<float>(dis(gen));

    float length = sqrt(newX * newX + newY * newY);
    if (length != 0) {
        newX /= length;
        newY /= length;
    }

    velocity = { newX * currentSpeed, newY * currentSpeed };
}

void Ball::separateFromBlock(RectangleShape rect) {
    FloatRect ballRect = getGlobalBounds();
    FloatRect blockRect = rect.getGlobalBounds();

    float overlapLeft = ballRect.left + ballRect.width - blockRect.left;
    float overlapRight = blockRect.left + blockRect.width - ballRect.left;
    float overlapTop = ballRect.top + ballRect.height - blockRect.top;
    float overlapBottom = blockRect.top + blockRect.height - ballRect.top;

    float minOverlap = min(min(overlapLeft, overlapRight), min(overlapTop, overlapBottom));

    if (minOverlap == overlapLeft) {

        reverseHorizontalVelocity();
        move(-overlapLeft, 0);
    }
    else if (minOverlap == overlapRight) {

        reverseHorizontalVelocity();
        move(overlapRight, 0);
    }
    else if (minOverlap == overlapTop) {
        reverseVerticalVelocity();
        move(0, -overlapTop);
    }
    else if (minOverlap == overlapBottom) {
        reverseVerticalVelocity();
        move(0, overlapBottom);
    }
}

void Ball::startRandomTrajectoryTimer(float delay) {
    randomTrajectoryTimerActive = true;
    randomTrajectoryTimer = delay;
}