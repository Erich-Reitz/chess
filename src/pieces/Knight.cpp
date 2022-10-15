#include "Knight.hpp"

Knight::Knight() {};

Knight::~Knight() {};

bool Knight::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    if (abs(original_x - dest_x) == abs(original_y - dest_y)) {
        return true;
    }
    return false;
}