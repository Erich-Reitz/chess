#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <cstdio>

#include "PieceType.hpp"
#include "Board.hpp"
#include "Move.hpp"

class Board;

class Piece : public sf::Drawable {
  public:
    typedef std::set<Move> (Board::*GenerateMovesFn)(const Position&, const Piece*) const;


    Piece(bool _white, PieceType _type) ;
    Piece(const Piece& rhs) ;
    Piece& operator=(const Piece& rhs);
    ~Piece() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(float x, float y);
    void setRadius(float radius);
    void setColor(sf::Color color);

    PieceColor getColor() const;

    bool hasMoved() const;
    void setMoved() ;
    PieceType getType() const ;



    void setOriginalColor();
    size_t getTimesMoved() const;


    std::set<Move> generateAllValidMoves(const Position& current, const Board& board) const {
        return (board.*generateMovesFn)(current, this);
    }
  private:
    size_t timesMoved;
    PieceColor color;
    sf::CircleShape piece = sf::CircleShape() ;
    PieceType type;
    GenerateMovesFn generateMovesFn;
};
