#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "Piece.hpp"


class Square : public sf::Drawable {
  public:
    Square() {};
    Square(bool white, float xPos, float yPos, float size, std::optional<Piece*> piece);
    Piece *getPiece();
    
    void draw(sf::RenderTarget &window) const ; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

  protected:
    bool white;
  private:
    std::optional<Piece*> piece;
    sf::RectangleShape shape; 
};
