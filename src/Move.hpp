#pragma once
#include "ValidPosition.hpp"
#include "PieceType.hpp"
#include <optional>

using position_pair = std::pair<ValidPosition, ValidPosition> ;

class Move {
 public:
  position_pair move;
  PieceColor colorMove;
  std::optional<ValidPosition> capturee = {};
  std::optional<position_pair> castlee = {};
  MoveType move_type = MoveType::NORMAL;
  std::optional<PieceType> promoteTo;


  Move(position_pair _move, PieceColor _colorMove) {
    this->move = _move;
    this->colorMove = _colorMove;
  }


  Move(position_pair _move, PieceColor _colorMove, std::optional<position_pair>  _castlee) {
    this->move = _move;
    this->colorMove = _colorMove;
    this->castlee = _castlee;
  }


  Move(position_pair _move, PieceColor _colorMove, std::optional<ValidPosition>  _capturee) {
    this->move = _move;
    this->colorMove = _colorMove;
    this->capturee = _capturee;
  }

  Move(position_pair _move, PieceColor _colorMove, std::optional<ValidPosition>  _capturee, std::optional<position_pair> _castlee,
       MoveType _move_type) {
    this->move = _move;
    this->colorMove = _colorMove;
    this->capturee = _capturee;
    this->castlee = _castlee ;
    this->move_type = _move_type ;
  }


  bool isCapture() const {
    return this->capturee.has_value();
  }

  ValidPosition getOriginalSquare() const {
    return this->move.first;
  }

  ValidPosition getDestination() const {
    return this->move.second;
  }

  bool operator<(const Move &rhs) const  {
    return this->move < this->move && this->colorMove == rhs.colorMove;
  }
};