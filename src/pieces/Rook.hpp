#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "../Piece.hpp"

class Rook : public Piece {
  public:
    Rook();
    ~Rook();

    bool canMove(int originalx, int originaly, int destx, int desty) const override;
};

