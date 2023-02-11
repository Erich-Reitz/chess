#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"
#include "Position.hpp"

#include "chess_exceptions.cpp"

World::World() = default;


World::~World() = default;

std::optional<Move> setOfMovesContainsDestination(const std::set<Move>  &moveSet, const Position& destination) {
    for (auto move : moveSet) {
        if (move.moveTo == destination) {
            return move;
        }
    }

    return {};
}


void World::moveSelectedPiece(const Position &destination) {
    auto validMoves = this->selectedPieceInformation.placesCanMove.value();
    auto validMove = setOfMovesContainsDestination(validMoves, destination) ;

    if (validMove.has_value()) {
        try {
            gameBoard.processMove(validMove.value()) ;

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



bool sameColor(Piece *a, Piece *b) {
    return a->getColor() == b->getColor();
}

void World::handleMouseDownWithSelectedPiece(const Position& pressedSquare) {
    Piece  *previouslySelectedPiece = this->selectedPieceInformation.getPiece();
    std::optional<Piece*> pieceAtPosition = gameBoard.pieceAtPosition(pressedSquare) ;

    if (!pieceAtPosition.has_value()) {
        this->moveSelectedPiece(pressedSquare);
        return;
    }

    if (sameColor(pieceAtPosition.value(), previouslySelectedPiece)) {
        handleUserReselectingPiece(pressedSquare);
        return;
    }

    moveSelectedPiece(pressedSquare);
}

void World::displayValidMoves( ) {
    auto validMoves = this->selectedPieceInformation.getPlacesCanMove();

    for (auto &move : validMoves) {
        gameBoard.setSquareColor(move.moveTo, sf::Color::Green);
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

    if (!piece.has_value()) {
        return;
    }

    if (piece.value()->getColor() == this->gameBoard.getColorToMove()) {
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


