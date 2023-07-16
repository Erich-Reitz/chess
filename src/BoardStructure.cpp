#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "BoardStructure.hpp"
#include "Piece.hpp"

std::optional<Piece*> initial_piece(int row, int col) {
    bool isWhitePiece = row == 6 || row == 7;

    if (row == 0 || row == 7) {
        switch (col) {
        case 0:
            return new Piece(isWhitePiece, PieceType::ROOK) ;

        case 1:
            return new Piece(isWhitePiece, PieceType::KNIGHT) ;

        case 2:
            return new Piece(isWhitePiece, PieceType::BISHOP) ;

        case 3:
            return new Piece(isWhitePiece, PieceType::QUEEN) ;

        case 4:
            return new Piece(isWhitePiece, PieceType::KING) ;

        case 5:
            return new Piece(isWhitePiece, PieceType::BISHOP) ;

        case 6:
            return new Piece(isWhitePiece, PieceType::KNIGHT) ;

        case 7:
            return new Piece(isWhitePiece, PieceType::ROOK) ;

        default:
            throw RuntimeError();
        }
    }

    if (row == 1 || row == 6) {
        return new Piece(isWhitePiece, PieceType::PAWN);
    }

    return {};
}

BoardStructure::BoardStructure() {
    float initial_x_offset = 720.0;
    float initial_y_offset = 300.0;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            bool isWhite = (row + col) % 2 == 0;
            board[row][col] = new Square(isWhite, row, col, initial_x_offset + col * 50, initial_y_offset + row * 50, 50.f, initial_piece(row, col));
        }
    }
}

BoardStructure::BoardStructure(const BoardStructure& rhs) {
    *this = rhs;
}


BoardStructure& BoardStructure::operator=(const BoardStructure& rhs) {
    board.resize(8);

    for (int i = 0; i < 8; i++) {
        board[i].resize(8);

        for (int j = 0; j < 8; j++) {
            board[i][j] = new Square(*rhs.board[i][j]);
        }
    }

    return *this ;
}

void BoardStructure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            square->draw(target);
        }
    }
}

std::optional<ValidPosition> BoardStructure::getRowAndColOfMouse(const sf::Vector2f mousePos) const {
    for (const auto &row : this->board) {
        for (const auto &square : row) {
            if (square->getBoundaries().contains(mousePos)) {
                return square->getPosition();
            }
        }
    }

    return {};
}

Square* BoardStructure::squareAt(const ValidPosition& coord) const {
    return this->board.at(coord.r).at(coord.c);
}


Square* BoardStructure::squareAt(int row, int col) const {
    return this->board.at(row).at(col);
}