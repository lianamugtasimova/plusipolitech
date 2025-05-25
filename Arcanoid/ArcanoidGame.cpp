#include "ArcanoidGame.h"

Arcanoid::Arcanoid() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arñanoid"), font() {
    window.setFramerateLimit(60);


    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font arial.ttf!" << endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(Color::White);
    livesText.setPosition(WINDOW_WIDTH - 100, 10);

    paddle = Paddle();
    ball = Ball();
    floor = Floor();

    createBlocks();

    random_device rd;
    rng = mt19937(rd());

    ball.stickToPaddle(paddle);
}

void Arcanoid:: run() {
    Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleInput();
        update(dt);
        render();
    }
}

void Arcanoid:: handleInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Space && ball.isSticky()) {
                ball.releaseFromPaddle();
            }

            if (event.key.code == Keyboard::R) {
                resetLevel();
            }
        }
    }

    moveLeft = Keyboard::isKeyPressed(Keyboard::Left);
    moveRight = Keyboard::isKeyPressed(Keyboard::Right);
}

void Arcanoid::update(float dt) {
    paddle.update(dt, moveLeft, moveRight);

    if (!ball.isSticky()) {
        ball.update(dt);
    }
    else {
        ball.setPosition(paddle.getPosition().x + paddle.getSize().x / 2 - ball.getRadius(), paddle.getPosition().y - ball.getRadius() * 2);
    }


    if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
        ball.separateFromBlock(paddle);

    }
    if (ball.getPosition().y + ball.getRadius() * 2 > WINDOW_HEIGHT) {
        if (floor.isActivated() && !floor.isHidden()) {
            if (ball.getGlobalBounds().intersects(floor.getGlobalBounds())) {
                ball.reverseVerticalVelocity();
                floor.setHidden(true);
            }
        }
        else {
            lives--;
            if (lives <= 0) {
                resetLevel();
            }
            else {
                ball = Ball();
                ball.stickToPaddle(paddle);
            }
        }
    }

    applyBonus(dt);

    for (auto it = blocks.begin(); it != blocks.end();) {
        Block& block = *it;

        if (ball.getGlobalBounds().intersects(block.getGlobalBounds())) {
            if (block.getType() != BlockType::UNBREAKABLE) {
                score += 1;
            }
            ball.separateFromBlock(block);
            block.hit();

            if (block.getType() == BlockType::SPEED_UP) {
                ball.increaseSpeed(1.1f);
            }

            if (block.getType() == BlockType::BONUS) {
                collectBonus(block.getPosition().x, block.getPosition().y);
            }

            if (block.isDestroyed()) {
                it = blocks.erase(it);
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    scoreText.setString("Score: " + to_string(score));
    livesText.setString("Lives: " + to_string(lives));
}

void Arcanoid:: render() {
    window.clear();

    window.draw(paddle);
    window.draw(ball);

    if (floor.isActivated() && !floor.isHidden()) {
        window.draw(floor);
    }

    for (const auto& block : blocks) {
        window.draw(block);
    }

    for (const Bonus* bonus : bonuses) {
        window.draw(*bonus);
    }

    window.draw(scoreText);
    window.draw(livesText);
    window.display();
}

void Arcanoid::createBlocks() {
    blocks.clear();
    vector<int> weights = {
        30,  // NORMAL 
        10,   // UNBREAKABLE 
        40,  // BONUS 
        20   // SPEED_UP 
    };

    discrete_distribution<> dist({ weights.begin(), weights.end() });

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            int blockTypeIndex = dist(rng);
            BlockType type = static_cast<BlockType>(blockTypeIndex);
            int health = 1;

            Block block(STARTX + col * BLOCK_WIDTH, STARTY + row * BLOCK_HEIGHT, type);
            blocks.push_back(block);
        }
    }
}

void Arcanoid::resetLevel() {
    score = 0;
    lives = 3;
    paddle = Paddle();
    ball = Ball();
    floor = Floor();
    bonuses.clear();

    createBlocks();
    ball.stickToPaddle(paddle);
}

void Arcanoid::activateOneTimeFloor() {
    floor.activate();
    floor.setHidden(false);
}

void Arcanoid::applyBonus(float dt) {
    for (auto it = bonuses.begin(); it != bonuses.end(); ) {
        Bonus* bonus = *it;
        bonus->update(dt);

        if (bonus->getGlobalBounds().intersects(paddle.getGlobalBounds())) {
            if (PaddleBonus* paddleBonus = dynamic_cast<PaddleBonus*>(bonus)) {
                paddleBonus->applyToPaddle(paddle);
            }
            if (BallBonus* ballBonus = dynamic_cast<BallBonus*>(bonus)) {
                ballBonus->applyToBall(ball);
            }
            if (FloorBonus* floorBonus = dynamic_cast<FloorBonus*>(bonus)) {
                floorBonus->applyToFloor(floor);
            }
            delete bonus;
            it = bonuses.erase(it);
        }
        else if (bonus->getPosition().y > WINDOW_HEIGHT) {
            delete bonus;
            it = bonuses.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Arcanoid::collectBonus(float x, float y) {
    Bonus* newBonus = nullptr;
    int bonusTypeIndex = dist(rng) % 7;

    switch (static_cast<BonusType>(bonusTypeIndex)) {
    case BonusType::PADDLE_SIZE_INCREASE:
        newBonus = new PaddleSizeIncreaseBonus(x, y);
        break;
    case BonusType::PADDLE_SIZE_DECREASE:
        newBonus = new PaddleSizeDecreaseBonus(x, y);
        break;
    case BonusType::BALL_SPEED_UP:
        newBonus = new BallSpeedUpBonus(x, y);
        break;
    case BonusType::BALL_SPEED_DOWN:
        newBonus = new BallSpeedDownBonus(x, y);
        break;
    case BonusType::STICKY_BALL:
        newBonus = new StickyBallBonus(x, y);
        break;
    case BonusType::ONE_TIME_FLOOR:
        newBonus = new FloorBonus(x, y);
        break;
    case BonusType::RANDOM_TRAJECTORY:
        newBonus = new RandomTrajectoryBonus(x, y);
        break;
    }


    if (newBonus != nullptr) {
        bonuses.push_back(newBonus);
    }
}