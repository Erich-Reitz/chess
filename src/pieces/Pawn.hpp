#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "../Piece.hpp"
#include "PieceType.hpp"


class Pawn : public Piece {
  public:

    explicit Pawn(bool white);
    ~Pawn();

    bool canMove(int original_x, int original_y, int dest_x, int dest_y) const override;
  private:
    PieceType type = PieceType::pawn;

};

