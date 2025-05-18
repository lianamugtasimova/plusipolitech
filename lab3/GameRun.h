#pragma once
#include "Board.h"
using namespace sf;
class Game {
public:
    
    Game() : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GEMS Game") {
        window.setFramerateLimit(60);
        FirstClick = false;
        FirstGemX = FirstGemY = SecondGemX = SecondGemY = 0;
        selectedCell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        selectedCell.setFillColor(sf::Color::Transparent);
    }


    void run();
    GameBoard board;
    int FirstGemX, FirstGemY, SecondGemX, SecondGemY;

private:
    RenderWindow window;
    RectangleShape selectedCell;
    bool FirstClick;

    void draw();
    void update();
    void move(Event event);
    void firstClick(Event even);
    void secondClick(Event even);
};