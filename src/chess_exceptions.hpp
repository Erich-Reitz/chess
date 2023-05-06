#pragma once

#include <exception>

struct CurrentSquareDoesNotContainPiece : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "The current square does not contain a piece to move";
    }
};

struct PieceTypeSwitchFallthrough : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Unknown PieceType";
    }
};

struct RuntimeError : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Unexpected runtime error" ;
    }
};