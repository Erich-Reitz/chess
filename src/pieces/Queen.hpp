#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "../Piece.hpp"
#include "PieceType.hpp"


class Queen : public Piece {
  public:
    explicit Queen(bool white);
    ~Queen();

    bool canMove(int original_x, int original_y, int dest_x, int dest_y) const override;
  private:
    PieceType type = PieceType::queen;


};

