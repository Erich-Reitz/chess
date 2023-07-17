#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"

#include "Piece.hpp"

class Piece;

class Square : public GameObject {
  public:
    Square() = default;
    Square(bool white, ValidPosition position, float xPos, float yPos,  float size);
    Square(const Square& rhs);
    Square& operator=(const Square& rhs);
    std::optional<Piece*> getPiece() const;


    void setPiece(Piece* _piece);
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
    sf::Texture texture;
    ValidPosition position;
    float size;


};
