#include <functional>
#include <iostream>
#include <optional>

#include "Board.hpp"
#include "Piece.hpp"
#include "pieces/Rook.hpp"

std::optional<Piece*> inital_piece(int x, int y) {
    // if (x == 0 || x == 7) {
    //     switch (y) {
    //     case 0:
    //         return new Rook(false) ;
    //     case 1:
    //         return new Knight(false) ;
    //     case 2:
    //         return new Bishop(false);
    //     case 3:
    //         return new Queen(false) ;
    //     case 4:
    //         return new King(false) ;
    //     case 5:
    //         return new Bishop(false);
    //     case 6:
    //         return new Knight(false) ;
    //     case 7:
    //         return new Rook(false) ;
    //     }
    // }
    // if (x == 1 || x == 6) {
    //     return new Pawn(x == 1)
    // }
    if ((x == 0 || x == 7) && y == 0) {
        return new Rook();
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

