#include "Position.hpp"

Position::Position() {};

Position::Position(int row, int col) {
    this->row = row;
    this->col = col;
}

bool Position::operator==(const Position& rhs) {
    return this->row == rhs.row && this->col == rhs.col;
}

Position::~Position() {};