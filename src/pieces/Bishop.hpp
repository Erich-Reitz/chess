#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "PieceType.hpp"
#include "../Piece.hpp"

class Bishop : public Piece {
  public:

    explicit Bishop(bool white) ;
    ~Bishop();

    bool canMove(int original_x, int original_y, int dest_x, int dest_y) const override;
  private:
    PieceType type = PieceType::bishop;
};

