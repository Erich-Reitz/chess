#ifndef POSITION_HPP
#define POSITION_HPP

class Position {
  public:
    Position(int col, int row) {
        this->x = col;
        this->y = row;
    }
    int x;
    int y;
};

#endif