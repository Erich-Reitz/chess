#pragma once

#include <ostream>

class Position {
  public:
    Position();
    Position(int row, int col);
    friend std::ostream& operator<< (std::ostream& stream, const Position& position) {
        stream << position.row << " " << position.col;
        return stream;
    }
    ~Position();
    bool operator==(const Position& rhs) ;

    int row;
    int col;
};