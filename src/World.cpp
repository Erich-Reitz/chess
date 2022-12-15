#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <assert.h>     /* assert */

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



void World::handleMouseDownWithSelectedPiece(const Position& pressedSquare) {
    if (gameBoard.hasPieceAtPosition(pressedSquare)) {
        Piece  *previouslySelectedPiece = gameBoard.pieceAtPosition(this->previouslySelectedCoordinatesOfPiece.value()).value();
        if (gameBoard.pieceAtPosition(pressedSquare).value()->isWhite() == previouslySelectedPiece->isWhite()) {
            previouslySelectedPiece->setOriginalColor();
            handleMouseDownWithNoSelectedPiece(pressedSquare) ;
        } else {
            if (gameBoard.canMove(previouslySelectedCoordinatesOfPiece.value(), pressedSquare)) {
                //
                try {
                    gameBoard.move(previouslySelectedCoordinatesOfPiece.value(), pressedSquare);
                } catch (CurrentSquareDoesNotContainPiece &e) {
                    std::cerr << e.what() << std::endl;
                }
                // erase previously selected
                Piece  *piece = gameBoard.pieceAtPosition(pressedSquare).value();
                piece->setOriginalColor();
                previouslySelectedCoordinatesOfPiece = {};
                return;
            }
        }
    } else {
        if (gameBoard.canMove(previouslySelectedCoordinatesOfPiece.value(), pressedSquare)) {
            //
            try {
                gameBoard.move(previouslySelectedCoordinatesOfPiece.value(), pressedSquare);
            } catch (CurrentSquareDoesNotContainPiece &e) {
                std::cerr << e.what() << std::endl;
            }
            // erase previously selected
            Piece  *piece = gameBoard.pieceAtPosition(pressedSquare).value();
            piece->setOriginalColor();
            previouslySelectedCoordinatesOfPiece = {};
            return;
        }
    }
}

void World::handleMouseDownWithNoSelectedPiece(const Position& pressedSquare) {
    std::optional<Piece*>  piece = gameBoard.pieceAtPosition(pressedSquare) ;
    if (piece.has_value()) {
        previouslySelectedCoordinatesOfPiece = pressedSquare;
        piece.value()->setColor(sf::Color::Red);
    }
}

void World::handleMouseDownOnSquare(const Position& pressedSquare) {
    if (havePreviouslySelectedCoordinates()) {
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

bool World::havePreviouslySelectedCoordinates() const {
    return this->previouslySelectedCoordinatesOfPiece.has_value();
}

