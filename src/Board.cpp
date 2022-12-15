#include <functional>
#include <optional>

#include "Board.hpp"
#include "Piece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "Position.hpp"

#include "chess_exceptions.cpp"


std::optional<Piece*> initial_piece(int row, int col) {
    bool isWhitePiece = row == 6 || row == 7;
    if (row == 0 || row == 7) {
        switch (col) {
        case 0:
            return new Rook(isWhitePiece) ;
        case 1:
            return new Knight(isWhitePiece) ;
        case 2:
            return new Bishop(isWhitePiece);
        case 3:
            return new Queen(isWhitePiece) ;
        case 4:
            return new King(isWhitePiece) ;
        case 5:
            return new Bishop(isWhitePiece);
        case 6:
            return new Knight(isWhitePiece) ;
        case 7:
            return new Rook(isWhitePiece) ;
        default:
            throw RuntimeError();
        }
    }
    if (row == 1 || row == 6) {
        return new Pawn(isWhitePiece);
    }
    return {};
}

Board::Board() {
    int initial_x_offset = 720;
    int initial_y_offset = 300;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            bool isWhite = (row + col) % 2 == 0;
            board[row][col] = new Square(isWhite, row, col, initial_x_offset + col * 50, initial_y_offset + row * 50, 50.f, initial_piece(row, col));
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            square->draw(target);
        }
    }
}

std::optional<Piece*> Board::selectedPiece(const sf::Vector2f mousePos) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            if (square->getBoundaries().contains(mousePos)) {
                return square->getPiece();
            }
        }
    }
    return {};
}

std::optional<Square*> Board::selectedSquare(const sf::Vector2f mousePos) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            if (square->getBoundaries().contains(mousePos)) {
                return square;
            }
        }
    }
    return {};
}

std::optional<Position> Board::getRowAndColOfMouse(const sf::Vector2f mousePos) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            if (square->getBoundaries().contains(mousePos)) {
                return square->getPosition();
            }
        }
    }
    return {};
}

std::vector<Position> Board::generateAllValidMovesForPiece(const Position& current, const Piece *piece) const {
    std::vector<Position> validMoves;
    bool isPieceWhite = piece->isWhite();
    Position oneSpaceForward = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col) ;
    Position oneSpaceForwardOneSpaceRight = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col + (isPieceWhite ? 1 : -1)) ;
    if (piece->getType() == PieceType::pawn) {
        if (!piece->hasMoved()) {
            Position twoSpacesForward = Position(current.row + (isPieceWhite ? - 2 : 2), current.col) ;
            if (!hasPieceAtPosition(twoSpacesForward)) {
                validMoves.emplace_back(twoSpacesForward) ;
            }
        }
        if (!hasPieceAtPosition(oneSpaceForward)) {
            validMoves.emplace_back(oneSpaceForward)  ;
        }
        if (hasPieceAtPosition(oneSpaceForwardOneSpaceRight)) {
            validMoves.emplace_back(oneSpaceForwardOneSpaceRight) ;
        }
    }
    return validMoves;
}

bool Board::canMove(const Position& current, const Position& destination) const {
    // check if it's possible for the piece
    std::optional<Piece*> optPiece = pieceAtPosition(current);
    if (!optPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }
    // generate all moves for piece off a piece::type variable
    Piece *piece = optPiece.value();
    std::vector<Position> allValidPositions = generateAllValidMovesForPiece(current, piece);
    if (std::find(allValidPositions.begin(), allValidPositions.end(), destination) != allValidPositions.end()) {
        return true;
    }
    return false;
}

std::optional<Piece*> Board::pieceAtPosition(const Position& pos) const {
    return this->board[pos.row][pos.col]->getPiece();
}



bool Board::hasPieceAtPosition(int row, int col) const {
    return this->board[row][col]->getPiece().has_value();
}


bool Board::hasPieceAtPosition(const Position& pos) const {
    return this->board[pos.row][pos.col]->getPiece().has_value();
}


void Board::removePieceFromSquare(const Position& coordinates) {
    this->board[coordinates.row][coordinates.col]->removePiece();
}


void Board::move(const Position& current, const Position& destination) {
    std::optional<Piece*> userSelectedPiece = pieceAtPosition(current);
    if (!userSelectedPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }
    Piece *movingPiece = userSelectedPiece.value();
    removePieceFromSquare(current);
    this->board[destination.row][destination.col]->setPiece(movingPiece);
    movingPiece->setMoved(true);
}