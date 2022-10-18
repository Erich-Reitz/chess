#include "World.hpp"
#include "Board.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

World::World() {
}

World::World(sf::Vector2f l_size) {
}

World::~World() {}

void World::handleMouseDownWithSelectedPiece() {}

void World::HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp) {
    std::optional<Square*> pressedSquare;
    if (mouseDown) {
        pressedSquare = gameBoard.selectedSquare(mousePos);
        if (!pressedSquare.has_value()) {
            return;
        }
        std::optional<Piece*> piece = pressedSquare.value()->getPiece();
        if (!piece.has_value()) {
            return;
        }
    }
    return;
}


void World::Render(sf::RenderWindow& window) {
    window.draw(gameBoard);
}

void World::update(sf::Time deltaTime) {
}

bool World::havePieceSelected() const {
    return this->pieceSelected.has_value();
}

