#pragma once

class Position {
  public:
    Position();
    Position(int row, int col);
    ~Position();
    bool operator==(const Position& rhs) ;

    int row;
    int col;
};