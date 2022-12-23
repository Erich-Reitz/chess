#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "Piece.hpp"
#include "Position.hpp"


class Square : public sf::Drawable {
  public:
    Square() {};
    Square(bool white, int row, int col, float xPos, float yPos, float size, std::optional<Piece*> piece);
    std::optional<Piece*> getPiece() const;

    void setPiece(Piece* _piece);
    void setColor(sf::Color color);
    void removePiece();

    void draw(sf::RenderTarget &window) const ;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setOriginalColor();

    sf::FloatRect getBoundaries() const;
    Position getPosition() const;

  protected:
    bool white;
  private:
    std::optional<Piece*> piece;
    sf::RectangleShape shape;

    Position position;


};
