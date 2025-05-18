#include "Bonus.h"

std::unique_ptr<Bonus> Bonus:: createRandomBonus(int originX, int originY, GameBoard& board) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);

    if (dist(gen) < 50) {
        return std::make_unique<Recolor>(originX, originY, board);
    }
    else {
        return std::make_unique<Bomb>();
    }
}

void Bonus::placeInRandomCell(int originX, int originY, GameBoard& board) {
    int minX = std::max(0, originX - 3);
    int maxX = std::min(GRID_WIDTH - 1, originX + 3);
    int minY = std::max(0, originY - 3);
    int maxY = std::min(GRID_HEIGHT - 1, originY + 3);

    std::vector<std::pair<int, int>> possibleCells;
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            if (x != originX || y != originY) {
                possibleCells.emplace_back(x, y);
            }
        }
    }

    if (!possibleCells.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> cellDist(0, possibleCells.size() - 1);
        auto target = possibleCells[cellDist(gen)];
        apply(board, target.first, target.second);
    }
}

void Bonus:: spawnRandomBonus(int originX, int originY, GameBoard& board) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);

    if (dist(gen) < 20) {
        auto bonus = createRandomBonus(originX, originY, board);
        bonus->placeInRandomCell(originX, originY, board);
    }
}

void Recolor:: apply(GameBoard& board, int targetX, int targetY) {

    board.getGem(targetX, targetY)->setColor(originColor);
    std::vector<std::pair<int, int>> possibleTargets;

    int minX = std::max(0, targetX - 3);
    int maxX = std::min(GRID_WIDTH - 1, targetX + 3);
    int minY = std::max(0, targetY - 3);
    int maxY = std::min(GRID_HEIGHT - 1, targetY + 3);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            if ((abs(x - targetX) > 1 || abs(y - targetY) > 1) && (board.getGem(x, y)->getColor() != 6) && !(x == originX && y == originY)) {
                possibleTargets.emplace_back(x, y);
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(possibleTargets.begin(), possibleTargets.end(), g);

    int targetsToRecolor = std::min(2, static_cast<int>(possibleTargets.size()));
    for (int i = 0; i < targetsToRecolor; ++i) {
        int x = possibleTargets[i].first;
        int y = possibleTargets[i].second;
        board.getGem(x, y)->setColor(originColor);
    }
}

void Bomb:: apply(GameBoard& board, int targetX, int targetY) {
    std::vector<std::pair<int, int>> possibleTargets;

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (board.getGem(x, y)->isGemActive() && x != targetX && y != targetY && (board.getGem(x, y)->getColor() != 6)) {
                possibleTargets.emplace_back(x, y);
            }
        }
    }

    int gemsToDestroy = std::min(4, static_cast<int>(possibleTargets.size()));
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(possibleTargets.begin(), possibleTargets.end(), g);

    for (int i = 0; i < gemsToDestroy; ++i) {
        int x = possibleTargets[i].first;
        int y = possibleTargets[i].second;

        board.getGem(x, y)->setColor(6);
    }
    board.getGem(targetX, targetY)->setColor(6);
}