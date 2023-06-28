#pragma once
#include "ValidPosition.hpp"
#include "PieceType.hpp"
#include <optional>

using optional_move = std::optional<std::pair<ValidPosition, ValidPosition>> ;

class Move {
  public:
    std::pair<ValidPosition, ValidPosition> move;
    PieceColor colorMove;
    std::optional<ValidPosition> capturee = {};
    optional_move castlee = {};
    MoveType move_type = MoveType::NORMAL;
    std::optional<PieceType> promoteTo;


    Move(std::pair<ValidPosition, ValidPosition> _move, PieceColor _colorMove) {
        this->move = _move;
        this->colorMove = _colorMove;
    }

    Move(std::pair<ValidPosition, ValidPosition> _move, bool pieceIsWhite) {
        this->move = _move;

        if (pieceIsWhite) {
            this->colorMove = PieceColor::WHITE;

        } else {
            this->colorMove = PieceColor::BLACK;
        }
    }

    Move(std::pair<ValidPosition, ValidPosition> _move, PieceColor _colorMove, optional_move  _castlee) {
        this->move = _move;
        this->colorMove = _colorMove;
        this->castlee = _castlee;
    }


    Move(std::pair<ValidPosition, ValidPosition> _move, PieceColor _colorMove, std::optional<ValidPosition>  _capturee) {
        this->move = _move;
        this->colorMove = _colorMove;
        this->capturee = _capturee;
    }

    Move(std::pair<ValidPosition, ValidPosition> _move, PieceColor _colorMove, std::optional<ValidPosition>  _capturee, optional_move _castlee, MoveType _move_type) {
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

    ValidPosition getOriginalSquare() const {
        return this->move.first;
    }

    ValidPosition getDestination() const {
        return this->move.second;
    }

    bool operator<(const Move& rhs) const  {
        return this->move < this->move && this->colorMove == rhs.colorMove;
    }
};