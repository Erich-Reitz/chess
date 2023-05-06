#pragma once
#include "Position.hpp"
#include "PieceType.hpp"
#include <optional>

using optional_move = std::optional<std::pair<Position, Position>> ;

class Move {
  public:
    std::pair<Position, Position> move;
    PieceColor colorMove;
    std::optional<Position> capturee = {};
    optional_move castlee = {};
    MoveType move_type = MoveType::NORMAL;

    Move(std::pair<Position, Position> _move, PieceColor _colorMove) {
        this->move = _move;
        this->colorMove = _colorMove;
    }

    Move(std::pair<Position, Position> _move, PieceColor _colorMove, optional_move  _castlee) {
        this->move = _move;
        this->colorMove = _colorMove;
        this->castlee = _castlee;
    }


    Move(std::pair<Position, Position> _move, PieceColor _colorMove, std::optional<Position>  _capturee) {
        this->move = _move;
        this->colorMove = _colorMove;
        this->capturee = _capturee;
    }

    Move(std::pair<Position, Position> _move, PieceColor _colorMove, std::optional<Position>  _capturee, optional_move _castlee, MoveType _move_type) {
        this->move = _move;
        this->colorMove = _colorMove;
        this->capturee = _capturee;
        this->castlee = _castlee ;
        this->move_type = _move_type ;
    }


    bool isCapture() const {
        return this->capturee.has_value();
    }

    bool isCastle() const {
        return move_type == MoveType::CASTLE ;
    }

    bool isPawnPromotion() const {
        return move_type == MoveType::PAWN_PROMOTION;
    }

    bool operator<(const Move& rhs) const  {
        return this->move < this->move && this->colorMove == rhs.colorMove;
    }
};