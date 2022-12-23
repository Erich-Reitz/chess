#include <functional>
#include <optional>
#include <set>

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


std::set<Position> Board::generateAllValidMovesForPawn(const Position& current, const Piece *piece) const {
    std::set<Position> validMoves;
    bool isPieceWhite = piece->isWhite();
    bool oppositeColorOfPiece = !isPieceWhite;
    Position oneSpaceForward = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col) ;
    Position oneSpaceForwardOneSpaceRight = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col + (isPieceWhite ? 1 : -1)) ;
    Position oneSpaceForwardOneSpaceLeft = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col + (isPieceWhite ? -1 : 1)) ;
    if (!piece->hasMoved()) {
        Position twoSpacesForward = Position(current.row + (isPieceWhite ? - 2 : 2), current.col) ;
        if (!hasPieceAtPosition(twoSpacesForward)) {
            validMoves.insert(twoSpacesForward) ;
        }
    }
    if (!hasPieceAtPosition(oneSpaceForward)) {
        validMoves.insert(oneSpaceForward)  ;
    }
    if (hasPieceAtPosition(oneSpaceForwardOneSpaceRight, oppositeColorOfPiece)) {
        validMoves.insert(oneSpaceForwardOneSpaceRight) ;
    }
    if (hasPieceAtPosition(oneSpaceForwardOneSpaceLeft, oppositeColorOfPiece)) {
        validMoves.insert(oneSpaceForwardOneSpaceLeft) ;
    }
    return validMoves;
}

std::set<Position> Board::generateAllValidMovesForRook(const Position& current, const Piece *piece) const {
    std::set<Position> validMoves;
    bool pieceIsWhite = piece->isWhite();
    bool oppositeColorOfPiece = !pieceIsWhite;
    // moves down
    for (int row = current.row+1; row < 8; row++) {
        if (hasPieceAtPosition(row, current.col, oppositeColorOfPiece)) {
            validMoves.insert(Position(row, current.col)) ;
            break;
        } else if (hasPieceAtPosition(row, current.col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert(Position(row, current.col)) ;
        }
    }
    // moves up
    for (int row = current.row-1; row >= 0; row--) {
        if (hasPieceAtPosition(row, current.col, oppositeColorOfPiece)) {
            validMoves.insert(Position(row, current.col)) ;
            break;
        } else if (hasPieceAtPosition(row, current.col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert(Position(row, current.col)) ;
        }
    }
    return validMoves;
}

std::set<Position> Board::generateAllValidMovesForPiece(const Position& current, const Piece *piece) const {
    if (piece->getType() == PieceType::PAWN) {
        return generateAllValidMovesForPawn(current, piece) ;
    }
    if (piece->getType() == PieceType::ROOK) {
        return generateAllValidMovesForRook(current, piece);
    }
    return {};
}

bool Board::canMove(const Position& current, const Position& destination) const {
    // check if it's possible for the piece
    std::optional<Piece*> optPiece = pieceAtPosition(current);
    if (!optPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }
    Piece *piece = optPiece.value();
    std::set<Position> allValidPositions = generateAllValidMovesForPiece(current, piece);
    return allValidPositions.find(destination) != allValidPositions.end() ;
}

std::optional<Piece*> Board::pieceAtPosition(const Position& pos) const {
    return this->board[pos.row][pos.col]->getPiece();
}

bool Board::hasPieceAtPosition(const Position& pos) const {
    return this->board[pos.row][pos.col]->getPiece().has_value();
}

bool Board::hasPieceAtPosition(const Position& pos, const bool targetColorIsWhite) const {
    std::optional<Piece*> piece;
    try {
        piece = this->board.at(pos.row).at(pos.col)->getPiece();
    } catch (const std::out_of_range& exp) {
        return false;
    }
    if (! piece.has_value() ) {
        return false;
    }
    return piece.value()->isWhite() == targetColorIsWhite;
}

bool Board::hasPieceAtPosition(const size_t row, const size_t col, const bool targetColorIsWhite) const {
    auto piece = this->board[row][col]->getPiece();
    if (! piece.has_value() ) {
        return false;
    }
    return piece.value()->isWhite() == targetColorIsWhite;
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
    movingPiece->setMoved();
}