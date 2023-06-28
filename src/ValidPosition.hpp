#pragma once

#include <ostream>
#include <iostream>
#include "bounded.hpp"


class ValidPosition {
  public:
    ValidPosition() {} ;
    ValidPosition(bounded_value<int, 0,  7>  r, bounded_value<int, 0,  7>  c) {
        this->r = r;
        this->c = c;
    }

    friend std::ostream& operator<< (std::ostream& stream, const ValidPosition& ValidPosition) {
        stream << ValidPosition.r << " " << ValidPosition.c;
        return stream;
    }
    ~ValidPosition() {} ;
    bool operator==(const ValidPosition& rhs) const {
        return this->r == rhs.r && this->c == rhs.c;
    }

    bool operator<(const ValidPosition &rhs) const {
        if (this->r < rhs.r) {
            return true;
        }

        if (this->r > rhs.r) {
            return false;
        }

        return this->c < rhs.c;
    }

    bounded_value<int, 0,  7>   r;
    bounded_value<int, 0,  7>    c;
};