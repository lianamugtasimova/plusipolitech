#include "GameRun.h"

void Game::draw() {
    window.clear(sf::Color::Black);
	
    board.drawBoard(window);
	if (FirstClick) {
		window.draw(selectedCell); 
	}
    window.display();
}

void Game::update() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			break;
		case Event::MouseButtonReleased:
			move(event);
			if (board.checkMatches()) {
				board.removeMatches();
				while (board.checkMatches()) {
					board.removeMatches();
				}
			}
			if (board.areThereDeactive()) {
				board.gravity();
				board.newGems();
				while (board.checkMatches()) {
					board.removeMatches();
				}
			}
			
			break;
		}
	}
}

void Game::run() {

	while (window.isOpen()) {
		update();
		draw();
	}
}

void Game::firstClick(Event event) {
	if (event.mouseButton.button == Mouse::Left) {
		
		Vector2i localPositionFirstGem = Mouse::getPosition();
		FirstGemX = static_cast<int>(event.mouseButton.x / CELL_SIZE);
		FirstGemY = static_cast<int>(event.mouseButton.y / CELL_SIZE);

		selectedCell.setPosition(FirstGemX * CELL_SIZE, FirstGemY * CELL_SIZE);
		selectedCell.setOutlineThickness(3);
		selectedCell.setOutlineColor(Color::White);

		FirstClick = true;
	}
}

void Game::secondClick(Event event) {
	if (event.mouseButton.button == Mouse::Left) {

		Vector2i localPositionFirstGem = Mouse::getPosition();

		SecondGemX = static_cast<int>(event.mouseButton.x / CELL_SIZE);
		SecondGemY = static_cast<int>(event.mouseButton.y / CELL_SIZE);

		if ((abs(FirstGemX - SecondGemX) == 1 && FirstGemY == SecondGemY) ||
			(abs(FirstGemY - SecondGemY) == 1 && FirstGemX == SecondGemX)) {
			board.swapGems(FirstGemX, FirstGemY, SecondGemX, SecondGemY);
		}

		FirstClick = false;

	}
	if (event.mouseButton.button == Mouse::Right) {
		FirstClick = false;
	}

}

void Game::move(Event event) {
	if (!FirstClick) {
		firstClick(event);
	}
	else {
		secondClick(event);
	}
}