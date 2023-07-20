#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>

#include "PieceType.hpp"
#include "Move.hpp"
#include "GameObject.hpp"


class Piece  {
 public:
  Piece(PieceColor color, PieceType type);
  Piece(const Piece &rhs)  = default;
  Piece &operator=(const Piece &rhs);
  ~Piece() = default;

  bool hasMoved() const;
  size_t timesMoved = 0;
  PieceType type;
  PieceColor color;
 private:
};
