#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "pieces/PieceType.hpp"


class Piece : public sf::Drawable {
  public:
    Piece(bool white) ;
    virtual ~Piece();
    virtual bool canMove(int original_x, int original_y, int dest_x, int dest_y) const = 0;

    void draw(sf::RenderTarget &window) const ;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setXPos(float x);
    void setYPos(float y);
    void setPosition(float x, float y);
    void setRadius(float radius);
    void setColor(sf::Color color);

    bool isWhite() const;
    bool isBlack() const;

    bool hasMoved() const;
    void setMoved(bool hasMoved) ;

    void setOriginalColor();
  private:
    bool has_self_moved = false;
    bool white;
    sf::CircleShape piece = sf::CircleShape() ;
    PieceType type;
};
