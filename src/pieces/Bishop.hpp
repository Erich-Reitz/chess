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

    explicit Bishop(bool white);
    ~Bishop();

};

