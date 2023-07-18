#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>


#include "PieceType.hpp"
#include "Move.hpp"

class BoardState {
 public:
  BoardState() = default;
  BoardState(const BoardState &rhs);
  BoardState &operator=(const BoardState &rhs);
  ~BoardState() = default;

  void processMove(const Move &move) ;

  std::vector<Move> moveList;
  PieceColor colorToMove = PieceColor::WHITE ;
};
