#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "Piece.hpp"
#include "Position.hpp"

class Piece;

class Square : public sf::Drawable {
  public:
    Square() {};

    Square(bool white, int row, int col, float xPos, float yPos, float size, std::optional<Piece*> piece);
    Square(const Square& rhs);
    Square& operator=(const Square& rhs);
    std::optional<Piece*> getPiece() const;

    void setPiece(Piece* _piece);
    void removePiece();

    void draw(sf::RenderTarget &window) const ;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect getBoundaries() const;
    Position getPosition() const;

  protected:
    bool white;
  private:
    std::optional<Piece*> piece;
    sf::Sprite shape;
    sf::Texture texture;
    Position position;


};
