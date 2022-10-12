#include "Board.hpp"
#include <iostream>

Board::Board() {
    board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = new Square((row+col) % 2 == 0);
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    std::cout << "Board::draw" << std::endl;
    for (const auto &row : board) {
        for (const auto &square : row) {
            square->draw(target);
        }
    }
}

