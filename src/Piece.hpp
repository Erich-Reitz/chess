#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <cstdio>

#include "pieces/PieceType.hpp"


class Piece : public sf::Drawable {
  public:
    Piece(bool _white, PieceType _type) ;
    ~Piece() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(float x, float y);
    void setRadius(float radius);
    void setColor(sf::Color color);

    bool isWhite() const;

    bool hasMoved() const;
    void setMoved() ;
    PieceType getType() const ;

    void setOriginalColor();
  private:
    size_t timesMoved = 0;
    PieceColor color;
    sf::CircleShape piece = sf::CircleShape() ;
    PieceType type;
};
