#include "Bonus.h"

Bonus::Bonus(float x, float y, BonusType type) : type(type) {
    setSize({ 20, 20 });
    setPosition(x, y);
    velocity = { 0, 100.f };
}

void Bonus::update(float dt) {
    move(velocity * dt);
}

BonusType Bonus::getType() const {
    return type; 
}

void Bonus:: setPosition(float x, float y) {
    RectangleShape::setPosition(x, y);
}