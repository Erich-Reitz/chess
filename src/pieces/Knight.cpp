#include "Knight.hpp"



Knight::Knight(bool white) : Piece(white) {};

Knight::~Knight() {};

bool Knight::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    int xDifference = abs(original_x - dest_x);
    int yDifference = abs(dest_y - original_y);
    if (xDifference == 2) {
        return yDifference == 1;
    }
    if (yDifference == 2) {
        return xDifference == 1;
    }
    return false;
}