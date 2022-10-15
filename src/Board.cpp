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


std::optional<Piece*> inital_piece(int x, int y) {
    bool isWhitePiece = y == 6 || y == 7;
    if (y == 0 || y == 7) {
        switch (x) {
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
    if (y == 1 || y == 6) {
        return new Pawn(isWhitePiece);
    }
    return {};
}

Board::Board() {
    board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));
    int inital_x_offset = 720;
    int inital_y_offset = 300;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = new Square((row+col) % 2 == 0, inital_x_offset + col * 50, inital_y_offset + row * 50, 50.f, inital_piece(col, row));
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

