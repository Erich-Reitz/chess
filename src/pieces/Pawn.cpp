#include "Pawn.hpp"

Pawn::Pawn() {};

Pawn::Pawn(bool white) : Piece(white) {};

Pawn::~Pawn() {};

bool Pawn::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    int yDifference = dest_y - original_y;
    if (yDifference >= 1 && this->isWhite()) {
        return false;
    }
    if (yDifference <= -1 && this->isBlack()) {
        return false;
    }
    int absYDifference = abs(yDifference);
    int absXDifference = abs(dest_x - original_x);
    if (absYDifference == 1 && (absXDifference == 0 || absXDifference == 1 )) {
        return true;
    }
    if (absYDifference == 2 && (absXDifference == 0 || absXDifference == 1 )) {
        if (this->hasMoved() == true) {
            return false;
        }
        return true;
    }
    return false;
}

