#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

#include "PieceType.hpp"
#include "Board.hpp"
#include "Move.hpp"

class Board;

class Piece : public sf::Drawable {
  public:
    using MoveFuncPtr = std::vector<Move> (*)(const Board*, const Position&, const Piece*);
    Piece(bool _white, PieceType _type) ;
    Piece(const Piece& rhs) ;
    Piece& operator=(const Piece& rhs);
    ~Piece() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(float x, float y);
    void setRadius(float radius);

    PieceColor getColor() const;

    bool hasMoved() const;
    void setMoved() ;
    PieceType getType() const ;
    size_t getTimesMoved() const;
    std::vector<Move> generateAllMoves(const Board* board, const Position& current, const Piece* piece) const {
        return m_moveFuncPtr(board, current, piece);
    }
  private:
    size_t timesMoved;
    PieceColor color;
    sf::Sprite piece;
    PieceType type;
    sf::Texture texture;
    MoveFuncPtr m_moveFuncPtr = nullptr;
};
