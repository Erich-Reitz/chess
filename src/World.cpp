#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"
#include "Position.hpp"

#include "chess_exceptions.cpp"

World::World() = default;


World::~World() = default;



void World::moveSelectedPiece(const Position &destination) {
    auto validMoves = this->selectedPieceInformation.placesCanMove.value();
    if (validMoves.find(destination) != validMoves.end()) {
        try {
            gameBoard.move(this->selectedPieceInformation.getCoordinates(), destination);
        } catch (CurrentSquareDoesNotContainPiece &e) {
            std::cerr << e.what() << std::endl;
        }
        this->selectedPieceInformation.reset();
        this->gameBoard.resetAllSquaresColor();
    }
}

void World::handleUserReselectingPiece(const Position& pressedSquare) {
    this->selectedPieceInformation.reset();
    this->gameBoard.resetAllSquaresColor();
    handleMouseDownWithNoSelectedPiece(pressedSquare) ;
}

void World::capturePiece(const Position& capturedPiecePosition) {
    this->moveSelectedPiece(capturedPiecePosition);
}

void World::handleMouseDownWithSelectedPiece(const Position& pressedSquare) {
    Piece  *previouslySelectedPiece = this->selectedPieceInformation.getPiece();
    if (gameBoard.hasPieceAtPosition(pressedSquare)) {
        if (gameBoard.pieceAtPosition(pressedSquare).value()->isWhite() == previouslySelectedPiece->isWhite()) {
            handleUserReselectingPiece(pressedSquare);
        } else {
            capturePiece(pressedSquare);
        }
    } else {
        this->moveSelectedPiece(pressedSquare);
    }
}

void World::displayValidMoves( ) {
    auto validMoves = this->selectedPieceInformation.getPlacesCanMove();
    for (auto &pos :validMoves) {
        gameBoard.setSquareColor(pos, sf::Color::Green);
    }
}

void World::displaySelectedPiece()  {
    this->selectedPieceInformation.getPiece()->setColor(sf::Color::Red);
}

void World::handleDisplayOfNewPieceSelected() {
    this->displayValidMoves();
    this->displaySelectedPiece();
}


void World::handleMouseDownWithNoSelectedPiece(const Position& pressedSquare) {
    std::optional<Piece*>  piece = gameBoard.pieceAtPosition(pressedSquare) ;
    if (piece.has_value()) {
        auto placesCanMove = gameBoard.generateAllValidMovesForPiece(pressedSquare, piece.value());
        this->selectedPieceInformation.setInformation(pressedSquare, piece.value(), placesCanMove);
        this->handleDisplayOfNewPieceSelected();
    }
}

void World::handleMouseDownOnSquare(const Position& pressedSquare) {
    if (this->selectedPieceInformation.hasSelectedPiece()) {
        return handleMouseDownWithSelectedPiece(pressedSquare);
    }
    return handleMouseDownWithNoSelectedPiece(pressedSquare);
}

void World::handleMouseDown(sf::Vector2f mousePos) {
    std::optional<Position> pressedPosition  = gameBoard.getRowAndColOfMouse(mousePos);
    if (!pressedPosition.has_value()) {
        return;
    }
    handleMouseDownOnSquare(pressedPosition.value());
}

void World::HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp) {
    if (mouseDown) {
        handleMouseDown(mousePos) ;
    }
}


void World::Render(sf::RenderWindow& window) {
    window.draw(gameBoard);
}

void World::update(sf::Time deltaTime) {
}


