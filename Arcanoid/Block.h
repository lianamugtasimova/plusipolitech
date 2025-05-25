#pragma once
#include "common.h"

enum class BlockType {
    NORMAL,
    UNBREAKABLE,
    BONUS,
    SPEED_UP
};

class Block : public RectangleShape {
public:
    Block(float x, float y, BlockType type);
    bool isDestroyed() const;
    void hit();
    BlockType getType() const;
    int getHealth() const;
    void setOutlineColorBasedOnHealth();
    void resetHitThisFrame();

private:
    BlockType type;
    int health = 3;
    Color original_color; 
    float outlineThickness; 
    Color outlineColor;
    bool hitThisFrame = false;
};