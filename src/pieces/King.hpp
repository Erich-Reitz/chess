#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "../Piece.hpp"

class King : public Piece {
  public:
    King();
    King(bool white);
    ~King();

    bool canMove(int original_x, int original_y, int dest_x, int dest_y) const override;
};
