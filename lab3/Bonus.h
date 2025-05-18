#pragma once
#include <random>
#include <vector>
#include <cmath>
#include "Board.h"

class Bonus {
public:

    virtual ~Bonus() = default;

    static std::unique_ptr<Bonus> createRandomBonus(int originX, int originY, GameBoard& board);

    static void spawnRandomBonus(int originX, int originY, GameBoard& board);

    virtual void apply(GameBoard& board, int targetX, int targetY) = 0;

protected:
    void placeInRandomCell(int originX, int originY, GameBoard& board);
};

class Recolor : public Bonus {
public:
    Recolor(int originX, int originY, GameBoard& board)
        : originX(originX), originY(originY), originColor(board.getGem(originX, originY)->getColor()) {}

    void apply(GameBoard& board, int targetX, int targetY) override;

private:
    int originX, originY;
    int originColor;
};


class Bomb : public Bonus {
public:
    Bomb() = default;
    void apply(GameBoard& board, int targetX, int targetY) override;
};