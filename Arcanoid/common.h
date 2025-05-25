#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_WIDTH = 80;
const float PADDLE_HEIGHT = 15;
static float const PADDLE_SPEED = 400.f;
static float const BALL_RADIUS = 7.5f;
static float const BALL_POSX = WINDOW_WIDTH / 2 - BALL_RADIUS;
static float const BALL_POSY = WINDOW_HEIGHT / 2 - BALL_RADIUS;
static float const BALL_VELOCITY_X = 200.f;
static float const BALL_VELOCITY_Y = 200.f;
static float const PADDLE_POX_X = WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2;
static float const PADDLE_POS_Y = WINDOW_HEIGHT - PADDLE_HEIGHT - 10;

const float BLOCK_WIDTH = 60;
const float BLOCK_HEIGHT = 30;
const int COLS = WINDOW_WIDTH / BLOCK_WIDTH;
const int ROWS = 3;
const float STARTX =WINDOW_WIDTH - COLS* (BLOCK_WIDTH);
const float STARTY = 50;

const int FLOOR_WIDTH = 800;
const int FLOOR_HEIGHT = 10;

static float const BALL_MAX_SPEED = 700.f;
static float const BALL_MIN_SPEED = 100.f;

static float const PADDLE_MAX_WIDTH = 200.f;
static float const PADDLE_MIN_WIDTH = 40.f;
