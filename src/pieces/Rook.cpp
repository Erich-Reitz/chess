#include "Rook.hpp"

Rook::Rook() {};

Rook::Rook(bool white) : Piece(white) {};

Rook::~Rook() {};

bool Rook::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    return original_x == dest_x || original_y == dest_y;
}