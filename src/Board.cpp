#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>

#include "Board.hpp"
#include "Piece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"

#include "chess_exceptions.cpp"


std::optional<Piece*> inital_piece(int row, int col) {
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
        }
    }
    if (row == 1 || row == 6) {
        return new Pawn(isWhitePiece);
    }
    return {};
}

Board::Board() {
    int inital_x_offset = 720;
    int inital_y_offset = 300;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            bool isWhite = (row + col) % 2 == 0;
            board[row][col] = new Square(isWhite, row, col, inital_x_offset + col * 50, inital_y_offset + row * 50, 50.f, inital_piece(row, col));
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

std::vector<Position> Board::generateAllValidMovesForPiece(const Position current, const Piece *piece) const {
    std::vector<Position> validMoves;
    if (piece->getType() == PieceType::pawn) {
        int oneSpaceForward = piece->isWhite() ? -1 : 1;
        int twoSpaceForward =  piece->isWhite() ? -2 : 2;
        if (!piece->hasMoved()) {
            if (!hasPieceAtPosition(current.row + twoSpaceForward, current.col)) {
                validMoves.push_back(Position(current.row+twoSpaceForward, current.col)) ;
            }
        }
        if (!hasPieceAtPosition(current.row + oneSpaceForward, current.col)) {
            validMoves.push_back(Position(current.row + oneSpaceForward, current.col)) ;
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
        std::cout << "can move " << current << " to " << destination << std::endl;
        return true;
    }
    std::cout << "cannot move " << current << " to " << destination << std::endl;
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
}