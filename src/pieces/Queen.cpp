#include "Queen.hpp"

Queen::Queen() {};

Queen::Queen(bool white) : Piece(white) {};

Queen::~Queen() {};

bool Queen::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    if (original_x == dest_x || original_y == dest_y) {
        return true;
    }
    if (abs(original_x - dest_x) == abs(original_y - dest_y)) {
        return true;
    }
    return false;
}