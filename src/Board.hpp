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
  protected:
    std::vector<std::vector<Square*>> board; 
};
