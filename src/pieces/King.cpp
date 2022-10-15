#include "King.hpp"

King::King() {};

King::~King() {};

bool King::canMove(int original_x, int original_y, int dest_x, int dest_y) const {
    if (original_x == dest_x && original_y == dest_y) {
        return false;
    }
    if (abs(original_x - dest_x) <= 1 && abs(original_y - dest_y) <= 1) {
        return true;
    }
    return false;
}