#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"
#include "Position.hpp"

#include "chess_exceptions.cpp"

World::World() {
}

World::World(sf::Vector2f l_size) {
}

World::~World() {}

void World::handleMouseDownWithSelectedPiece(Position pressedSquare) {
    if (gameBoard.canMove(previouslySelectedCoordinates.value(), pressedSquare)) {
        //
        try {
            gameBoard.move(previouslySelectedCoordinates.value(), pressedSquare);
        } catch (CurrentSquareDoesNotContainPiece &e) {
            std::cout << "CurrentSquareDoesNotContainPiece caught" << std::endl;
            std::cout << e.what() << std::endl;
        }
        previouslySelectedCoordinates = {};
        return;
    }
}

void World::handleMouseDownWithNoSelectedPiece(Position pressedSquare) {
    previouslySelectedCoordinates = pressedSquare;
}

void World::handleMouseDownOnSquare(Position pressedSquare) {
    if (havePreviouslySelectedCoordinates()) {
        return handleMouseDownWithSelectedPiece(pressedSquare);
    }
    return handleMouseDownWithNoSelectedPiece(pressedSquare);
}

void World::handleMouseDown(sf::Vector2f mousePos) {
    std::optional<Position> pressedPosition;
    pressedPosition = gameBoard.getRowAndColOfMouse(mousePos);
    if (!pressedPosition.has_value()) {
        std::cout << "did not select a square" << std::endl;
        // did not select a square
        return;
    }
    handleMouseDownOnSquare(pressedPosition.value());
}

void World::HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp) {
    if (mouseDown) {
        handleMouseDown(mousePos) ;
    }
    return;
}


void World::Render(sf::RenderWindow& window) {
    window.draw(gameBoard);
}

void World::update(sf::Time deltaTime) {
}

bool World::havePreviouslySelectedCoordinates() const {
    return this->previouslySelectedCoordinates.has_value();
}

