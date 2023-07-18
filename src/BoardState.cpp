#include "BoardState.hpp"
#include "oppositeColor.hpp"

BoardState::BoardState(const BoardState &rhs) {
  *this = rhs;
}

BoardState &BoardState::operator=(const BoardState &rhs) {
  this->colorToMove = rhs.colorToMove ;
  this->moveList = rhs.moveList;
  return *this ;
}

void BoardState::processMove(const Move &move) {
  this->moveList.push_back(move) ;
  this->colorToMove = opposite_color(this->colorToMove) ;
}