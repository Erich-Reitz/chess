#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"


#include "chess_exceptions.hpp"

World::World() {
    this->pawnPromotionDialog = sf::RectangleShape(sf::Vector2f(200, 200));
    this->pawnPromotionDialog.setFillColor(sf::Color::Red) ;
    this->pawnPromotionDialog.setOrigin(sf::Vector2f(100, 100));
}

World::~World() = default;

std::optional<Move> setOfMovesContainsDestination(const std::vector<Move>  &moveSet, const ValidPosition& destination) {
    for (const auto &move : moveSet) {
        if (move.getDestination() == destination) {
            return move;
        }
    }

    return {};
}

void World::displayPawnPromotionDialog() {
    this->pawnPromotionDialog.setPosition(this->m_viewCenter) ;
    this->worldState = WORLD_STATE::PAWN_PROMOTION_DIALOG;
}


void World::moveSelectedPiece(const ValidPosition &destination) {
    auto validMoves = this->selectedPieceInformation.placesCanMove.value();
    auto validMove = setOfMovesContainsDestination(validMoves, destination) ;

    if (!validMove.has_value()) {
        // the move that the user requested is invalid
        // leave the selected piece, and wait for another input
        return;
    }

    auto move_req = validMove.value();

    if (move_req.isPawnPromotion()) {
        // display pawn promotion dialog
        this->displayPawnPromotionDialog();
    }

    try {
        gameBoard.processMove(move_req) ;

    } catch (CurrentSquareDoesNotContainPiece &e) {
        std::cerr << e.what() << std::endl;
    }

    this->clearSelectedPieceInformation();
}

void World::clearSelectedPieceInformation() {
    this->selectedPieceInformation.reset();
    this->gameBoard.resetAllSquaresColor();
}

void World::handleUserReselectingPiece(const ValidPosition& pressedSquare) {
    this->clearSelectedPieceInformation();
    handleMouseDownOnBoardWithNoSelectedPiece(pressedSquare) ;
}



bool sameColor(Piece *a, Piece *b) {
    return a->getColor() == b->getColor();
}

void World::handleMouseDownOnBoardWithSelectedPiece(const ValidPosition& pressedSquare) {
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
        gameBoard.setSquareColor(move.getDestination(), sf::Color::Green);
    }
}

void World::displaySelectedPiece()  {
    // todo
}




void World::handleMouseDownOnBoardWithNoSelectedPiece(const ValidPosition& pressedSquare) {
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
        return handleMouseDownOnBoardWithSelectedPiece(pressedSquare);
    }

    return handleMouseDownOnBoardWithNoSelectedPiece(pressedSquare);
}

void World::handleMouseDownOnBoard(sf::Vector2f mousePos) {
    std::optional<ValidPosition> pressedValidPosition  = gameBoard.getRowAndColOfMouse(mousePos);

    if (!pressedValidPosition.has_value()) {
        return;
    }

    handleMouseDownOnSquare(pressedValidPosition.value());
}

void World::handleMouseDown(sf::Vector2f mousePos) {
    switch(this->worldState) {
    case WORLD_STATE::BOARD:
        this->handleMouseDownOnBoard(mousePos) ;
        break;

    case WORLD_STATE::PAWN_PROMOTION_DIALOG:
        this->handleMouseDownOnPawnPromotionDialog(mousePos) ;
        break;

    default:
        throw RuntimeError() ;
    }
}

void World::HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp) {
    if (mouseDown) {
        handleMouseDown(mousePos) ;
    }
}


void World::Render(sf::RenderWindow& window) {
    this->m_viewCenter = window.getView().getCenter();
    this->m_viewSize = window.getView().getSize() ;
    window.draw(gameBoard);

    if (this->worldState == WORLD_STATE::PAWN_PROMOTION_DIALOG) {
        window.draw(this->pawnPromotionDialog) ;
    }
}

void World::update(sf::Time deltaTime) {
}


