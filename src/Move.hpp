#pragma once
#include "Position.hpp"

struct Move {
    Position moveFrom;
    Position moveTo;
    PieceColor colorMove;
    std::optional<Position> captures = {};
    std::optional<Position> alsoMoveFrom = {};
    std::optional<Position> alsoMoveTo = {} ;

    bool isCapture() const {
        return captures.has_value();
    }
    bool operator<(const Move& rhs) const  {
        return this->moveTo < rhs.moveTo;
    }
};