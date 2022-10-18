#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include "Square.hpp"

class Board : public sf::Drawable {
  public:
    Board();
    void draw(sf::RenderWindow &window) const  {}; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::optional<Piece*> selectedPiece(sf::Vector2f mousePos) const;
    std::optional<Square*> selectedSquare(sf::Vector2f mousePos) const; 
  protected:
    std::vector<std::vector<Square*>> board; 
};
