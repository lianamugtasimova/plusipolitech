#pragma once
#include "Floor.h"
#include "Bonus.h"

class FloorBonus : public Bonus {
public:
    FloorBonus(float x, float y) : Bonus(x, y, BonusType::ONE_TIME_FLOOR) {
        setFillColor(Color::Yellow);
    }

    void applyToFloor(Floor& floor) {
        floor.activate();
    }
};