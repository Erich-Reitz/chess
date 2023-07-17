#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

#include "PieceType.hpp"
#include "Move.hpp"
#include "GameObject.hpp"


class Piece : public GameObject {
  public:
    Piece(bool _white, PieceType _type, float squareXPos, float squareYPos, sf::Texture* texture) ;
    Piece(const Piece& rhs) ;
    Piece& operator=(const Piece& rhs);
    ~Piece() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(float x, float y);
    void setRadius(float radius);


    bool hasMoved() const;
    size_t timesMoved;
    PieceType type;
    PieceColor color;
  private:
};
