#include "oppositeColor.hpp"

PieceColor opposite_color(PieceColor color) {
  return color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE ;
}