#ifndef SQUARE_HPP
#define SQUARE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "Piece.hpp"


class Square : public sf::Drawable {
  public:
    Square() {};
    Square(bool white);
    Square(bool white, Piece *piece);
    Piece *getPiece();
    
    void draw(sf::RenderTarget &window) const ; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

  protected:
    bool white;
    bool occupied = false;
  private:
    Piece *piece;
    sf::RectangleShape shape; 
};

#endif