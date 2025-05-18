#include "Board.h"
#include "Bonus.h"

void GameBoard::initializeBoard() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> colorDist(0, COLORS_COUNT - 1);
    std::uniform_int_distribution<> bonusDist(0, 99);

    board.resize(GRID_HEIGHT, std::vector<std::shared_ptr<Gem>>(GRID_WIDTH));

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            int color = colorDist(gen);

            board[i][j] = std::make_shared<Gem>(color);
        }
    }

}

std::shared_ptr<Gem> GameBoard:: getGem(int x, int y) {
	if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
		return nullptr;
	}
	return board[x][y];
}

void GameBoard::swapGems(int x1, int y1, int x2, int y2) {
	std::swap(board[x1][y1], board[x2][y2]);
}

void GameBoard::drawBoard(sf::RenderWindow& window) {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (board[i][j]->getColor() == 6) {
				board[i][j]->deactivate();

			}
            if (board[i][j]->isGemActive()) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                cell.setPosition(i * CELL_SIZE + 1, j * CELL_SIZE + 1);
                cell.setFillColor(getGemColor(board[i][j]->getColor()));
				cell.setFillColor(getGemColor(board[i][j]->getColor()));

                window.draw(cell);
				
            }
        }
    }
}

std::vector<std::pair<int, int>> GameBoard::findMatches() {
	std::vector<std::pair<int, int>> matches;
	std::vector<std::vector<bool>> marked(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH - 2; x++) {
			if (board[x][y]->isGemActive() &&
				board[x][y]->getColor() == board[x+1][y]->getColor() &&
				board[x][y]->getColor() == board[x+2][y]->getColor()) {

				for (int dx = 0; dx < 3; ++dx) {
					if (!marked[x + dx][y]) {
						matches.emplace_back(x + dx, y);
						marked[x + dx][y] = true;
					}
				}

				int extend = 3;
				while (x + extend < GRID_WIDTH &&
					board[x][y]->getColor() == board[x + extend][y]->getColor()) {
					if (!marked[x + extend][y]) {
						matches.emplace_back(x + extend, y);
						marked[x + extend][y] = true;
					}
					extend++;
				}
			}
		}
	}

	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT-2; y++) {
			if (board[x][y]->isGemActive() &&
				board[x][y]->getColor() == board[x][y + 1]->getColor() &&
				board[x][y]->getColor() == board[x][y+2]->getColor()) {

				for (int dy = 0; dy < 3; ++dy) {
					if (!marked[x][y + dy]) {
						matches.emplace_back(x, y + dy);
						marked[x][y + dy] = true;
					}
				}
				int extend = 3;
				while (y + extend < GRID_HEIGHT &&
					board[x][y]->getColor() == board[x][y + extend]->getColor()) {
					if (!marked[x][y + extend]) {
						matches.emplace_back(x, y + extend);
						marked[x][y + extend] = true;
					}
					extend++;
				}
			}
		}
	}

	return matches;
}
bool GameBoard::checkMatches() {
	return !findMatches().empty();
}

void GameBoard::removeMatches() {
	auto matches = findMatches();
	int originX, originY;
	for (const auto& pos : matches) {
		int x = pos.first;
		int y = pos.second;
		board[x][y]->deactivate();
		originX = x;
		originY = y;
	}
	gravity();
	newGems();
	spawnBonus(originX, originY);
}

bool GameBoard:: areThereDeactive() {
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT - 2; y++) {
			if (!board[x][y]->isGemActive()) {
				return true;
			}
		}
	}
	return false;
}

void GameBoard::gravity() {
	int maxEmptyCells = 0;
	int x1, x2, y1, y2;
	for (int x = 0; x < GRID_WIDTH; x++) {
		int empty = 0;
		for (int y = GRID_HEIGHT - 1; y > 0; y--) {
			if (!board[x][y]->isGemActive()) {
				empty++;
				for (int k = y; k > 0; k--) {

					x1 = x;
					y1 = k;
					x2 = x;
					y2 = k - 1;
					swapGems(x1, y1, x2, y2);
				}
			}
		}
		if (maxEmptyCells < empty)
			maxEmptyCells = empty;
	}
	while (maxEmptyCells > 0) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			for (int y = GRID_HEIGHT - 1; y > 0; y--) {
				if (!board[x][y]->isGemActive()) {
					maxEmptyCells = y;
					for (int k = y; k > 0; k--) {
						x1 = x;
						y1 = k;
						x2 = x;
						y2 = k - 1;
						swapGems(x1, y1, x2, y2);
					}
				}
			}
		}
		maxEmptyCells--;
	}
}

void GameBoard::newGems() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> colorDist(0, COLORS_COUNT - 1);

	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			if (!board[x][y]->isGemActive()) {
				board[x][y] = std::make_shared<Gem>(colorDist(gen));
			}
		}
	}
}

void GameBoard::spawnBonus(int originX, int originY) {
	Bonus::spawnRandomBonus(originX, originY, *this);
}