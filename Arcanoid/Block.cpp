#include "Block.h"
#include <cmath>

Block::Block(float x, float y, BlockType type) : type(type), outlineThickness(2.0f) {
    setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    setPosition(x, y);
    original_color = Color::Blue;
    setFillColor(original_color);

    setOutlineThickness(outlineThickness); 
    setOutlineColor(sf::Color::Green);  

    switch (type) {
    case BlockType::NORMAL:
        setFillColor(original_color);
        health = 3;
        break;
    case BlockType::UNBREAKABLE:
        setFillColor(sf::Color::Red);
        health = -1;
        break;
    case BlockType::BONUS:
        setFillColor(Color::Magenta);
        health = 2;
        break;
    case BlockType::SPEED_UP:
        setFillColor(Color::Cyan);
        health = 1;
        break;
    }
}

void Block:: hit() {
    if (type != BlockType::UNBREAKABLE) {
        if (health > 0) {
            health--;

            setOutlineColorBasedOnHealth();
            hitThisFrame = true;
        }
    }
}

bool Block::isDestroyed() const { 
    return health == 0; 
}

BlockType Block:: getType() const { 
    return type; 
}

int Block:: getHealth() const { 
    return health; 
}

void Block:: setOutlineColorBasedOnHealth() {
    if (health > 2) {
        outlineColor = Color::Green;
        outlineThickness = 4;
    }
    else if (health == 2) {
        outlineColor = Color::Yellow;
        outlineThickness = 3;
    }
    else if (health == 1) {
        outlineColor = Color::White;
        outlineThickness = 2;
    }
    else {
        outlineColor = Color::Transparent;
    }
    setOutlineThickness(outlineThickness);
    setOutlineColor(outlineColor);
}

void Block:: resetHitThisFrame() {
    hitThisFrame = false;
}
