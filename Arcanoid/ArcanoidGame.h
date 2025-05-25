#include "common.h"
#include "Paddle.h"
#include "Ball.h"
#include "Floor.h"
#include "Block.h"
#include "Bonus.h"
#include "BallBonus.h"
#include "PaddleBonus.h"
#include "FloorBonus.h"

class Arcanoid {
public:
    Arcanoid();
    void run();

private:
    void handleInput();
    void update(float dt);
    void render();
    void createBlocks();
    void resetLevel();
    void activateOneTimeFloor();
    void applyBonus(float dt);
    void collectBonus(float x, float y);
    RenderWindow window;
    Paddle paddle;
    Ball ball;
    Floor floor;

    vector<Block> blocks;
    vector<Bonus*> bonuses;

    int score = 0;
    int lives = 3;
    bool moveLeft = false;
    bool moveRight = false;

    Font font;
    Text scoreText;
    Text livesText;


    mt19937 rng; 
    uniform_int_distribution<> dist{ 0, 7 };
};
