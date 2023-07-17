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
#include "GameObject.hpp"

class Board;

class Piece : public GameObject {
  public:
    using MoveFuncPtr = std::vector<Move> (*)(const Board*, const ValidPosition&, const Piece*);
    Piece(bool _white, PieceType _type, float squareXPos, float squareYPos) ;
    Piece(const Piece& rhs) ;
    Piece& operator=(const Piece& rhs);
    ~Piece() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(float x, float y);
    void setRadius(float radius);


    bool hasMoved() const;
    std::vector<Move> generateAllMoves(const Board* board, const ValidPosition& current, const Piece* piece) const {
        return m_moveFuncPtr(board, current, piece);
    }
    size_t timesMoved;
    PieceType type;
    PieceColor color;
  private:
    sf::Texture texture;
    MoveFuncPtr m_moveFuncPtr = nullptr;
};
