#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "Piece.hpp"
#include "ValidPosition.hpp"

class Square : public sf::Drawable {
  public:
    Square() {};

    Square(bool white, bounded_value<int, 0,  7>   row, bounded_value<int, 0,  7>   col, float xPos, float yPos, float size, std::optional<Piece*> piece);
    Square(const Square& rhs);
    Square& operator=(const Square& rhs);
    std::optional<Piece*> getPiece() const;


    void setPiece(Piece* piece);
    void removePiece();

    void draw(sf::RenderTarget &window) const ;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;



    sf::FloatRect getBoundaries() const;
    ValidPosition getPosition() const;

    void setPieceSize();

  protected:
    bool white;
  private:
    std::optional<Piece*> piece;
    sf::Sprite shape;
    sf::Texture texture;
    ValidPosition position;
    float size;



};
