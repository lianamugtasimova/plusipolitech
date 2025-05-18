#pragma once
#include "Gems.h"
using namespace sf;

class GameBoard {
public:
    GameBoard() {
        initializeBoard();
    }

    std::shared_ptr<Gem> getGem(int x, int y);

    void initializeBoard();
    void drawBoard(sf::RenderWindow& window);
    void swapGems(int x1, int y1, int x2, int y2);

    void newGems();
    void gravity();
    void spawnBonus(int x, int y);

    std::vector<std::pair<int, int>> findMatches();
    bool checkMatches();
    void removeMatches();
    bool areThereDeactive();

private:
    std::vector<std::vector<std::shared_ptr<Gem>>> board;

    Color getGemColor(int colorIndex) {
        static const std::vector<sf::Color> colors = {
            sf::Color::Red,    
            sf::Color::Blue,  
            sf::Color::Green,  
            sf::Color::Yellow, 
            sf::Color::Cyan,  
            sf::Color::Magenta, 
            sf::Color::Black, 
        };

        return colors[colorIndex % colors.size()];
    }
};
