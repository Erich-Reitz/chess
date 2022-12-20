#include "Position.hpp"

Position::Position() = default;;

Position::Position(int row, int col) {
    this->row = row;
    this->col = col;
}

bool Position::operator==(const Position& rhs) const {
    return this->row == rhs.row && this->col == rhs.col;
}

bool Position::operator<(const Position &rhs) const {
    if (this->row < rhs.row) {
        return true;
    }
    if (this->row > rhs.row) {
        return false;
    }
    return this->col < rhs.col;
}

Position::~Position() = default;;