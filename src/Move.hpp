#pragma once
#include "Position.hpp"

struct Move {
    Position moveTo;
    std::optional<Position> captures = {};

    bool isCapture() const {
        return captures.has_value();
    }
    bool operator<(const Move& rhs) const  {
        return this->moveTo < rhs.moveTo;
    }
};