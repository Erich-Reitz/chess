#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "Position.cpp"

class Piece {
  public:
    Piece() {};
    virtual ~Piece() {};
    virtual std::string getName() {
        return name;
    }
    virtual char getChar() {
        return name[0];
    }
    virtual bool isWhite() {
        return white;
    }
    virtual bool canMove(Position cur, Position dest) {
        return true;
    }
  private:
    bool white;
    std::string name;
};

#endif