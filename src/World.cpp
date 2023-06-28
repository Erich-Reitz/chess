#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"


#include "chess_exceptions.hpp"

World::World() = default;


World::~World() = default;

std::optional<Move> setOfMovesContainsDestination(const std::vector<Move>  &moveSet, const ValidPosition& destination) {
    for (auto move : moveSet) {
        if (move.move.second == destination) {
            return move;
        }
    }

    return {};
}


void World::moveSelectedPiece(const ValidPosition &destination) {
    auto validMoves = this->selectedPieceInformation.placesCanMove.value();
    auto validMove = setOfMovesContainsDestination(validMoves, destination) ;

    if (validMove.has_value()) {
        auto move_req = validMove.value();

        if (move_req.isPawnPromotion()) {
            // display pawn promotion dialog
            std::string selected_piece_type;
            std::cout << "enter piece type: (q, r, b, k): ";
            std::cin >> selected_piece_type ;

            if (selected_piece_type == "q") {
                move_req.promoteTo = PieceType::QUEEN;
            }
        }

        try {
            gameBoard.processMove(move_req) ;

        } catch (CurrentSquareDoesNotContainPiece &e) {
            std::cerr << e.what() << std::endl;
        }

        this->selectedPieceInformation.reset();
        this->gameBoard.resetAllSquaresColor();
    }
}

void World::handleUserReselectingPiece(const ValidPosition& pressedSquare) {
    this->selectedPieceInformation.reset();
    this->gameBoard.resetAllSquaresColor();
    handleMouseDownWithNoSelectedPiece(pressedSquare) ;
}



bool sameColor(Piece *a, Piece *b) {
    return a->getColor() == b->getColor();
}

void World::handleMouseDownWithSelectedPiece(const ValidPosition& pressedSquare) {
    Piece  *previouslySelectedPiece = this->selectedPieceInformation.getPiece();
    std::optional<Piece*> pieceAtValidPosition = gameBoard.pieceAtPosition(pressedSquare) ;

    if (pieceAtValidPosition.has_value() && sameColor(pieceAtValidPosition.value(), previouslySelectedPiece) ) {
        handleUserReselectingPiece(pressedSquare);
        return;
    }

    moveSelectedPiece(pressedSquare);
}

void World::displayValidMoves( ) {
    auto validMoves = this->selectedPieceInformation.getPlacesCanMove();

    for (auto &move : validMoves) {
        gameBoard.setSquareColor(move.move.second, sf::Color::Green);
    }
}

void World::displaySelectedPiece()  {
    // todo
}




void World::handleMouseDownWithNoSelectedPiece(const ValidPosition& pressedSquare) {
    std::optional<Piece*>  piece = gameBoard.pieceAtPosition(pressedSquare) ;

    if (!piece.has_value()) {
        return;
    }

    if (piece.value()->getColor() == this->gameBoard.getColorToMove()) {
        auto placesCanMove = gameBoard.generateAllValidMovesForPiece(pressedSquare, piece.value());
        this->selectedPieceInformation.setInformation(pressedSquare, piece.value(), placesCanMove);
        this->displayValidMoves();
        this->displaySelectedPiece();
    }
}

void World::handleMouseDownOnSquare(const ValidPosition& pressedSquare) {
    if (this->selectedPieceInformation.hasSelectedPiece()) {
        return handleMouseDownWithSelectedPiece(pressedSquare);
    }

    return handleMouseDownWithNoSelectedPiece(pressedSquare);
}

void World::handleMouseDown(sf::Vector2f mousePos) {
    std::optional<ValidPosition> pressedValidPosition  = gameBoard.getRowAndColOfMouse(mousePos);

    if (!pressedValidPosition.has_value()) {
        return;
    }

    handleMouseDownOnSquare(pressedValidPosition.value());
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


