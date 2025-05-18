#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;
const int CELL_SIZE = 80;
const int WINDOW_WIDTH = GRID_WIDTH * CELL_SIZE;
const int WINDOW_HEIGHT = GRID_HEIGHT * CELL_SIZE;
const int COLORS_COUNT = 6;
