#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "Piece.hpp"
#include "Position.hpp"

class Rook : public Piece {
  public:
    Rook(); 
    ~Rook(); 
    
    bool canMove(Position cur, Position dest) const override {
      return cur.x == dest.x || cur.y == dest.y;   
    }
  
};

