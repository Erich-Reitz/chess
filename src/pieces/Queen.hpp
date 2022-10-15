#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "../Piece.hpp"

class Queen : public Piece {
  public:
    Queen();
    Queen(bool white);
    ~Queen();

    bool canMove(int original_x, int original_y, int dest_x, int dest_y) const override;
};

