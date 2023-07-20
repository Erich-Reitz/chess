#include "Piece.hpp"
#include "PieceType.hpp"

Piece::Piece(PieceColor color, PieceType type)  {
  this->color = color;
  this->type = type;
}


Piece &Piece::operator=(const Piece &rhs) {
  if (this != &rhs) {
    color = rhs.color;
    type = rhs.type;
    timesMoved = rhs.timesMoved;
  }
  return *this;
}


bool Piece::hasMoved() const {
  return this->timesMoved != 0;
}