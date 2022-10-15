#include <string>
#include <iostream>

#include "Square.hpp"


Square::Square(bool white, float xPos, float yPos, float size, std::optional<Piece*> _piece ) {
    this->white = white;
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setPosition(sf::Vector2f(xPos, yPos));
    if (white) {
        this->shape.setFillColor(sf::Color::Yellow);
    } else {
        this->shape.setFillColor(sf::Color::Magenta);
    }
    if (_piece.has_value()) {
        this->piece = _piece;
        this->piece.value()->setPosition(xPos, yPos) ;
        this->piece.value()->setRadius(size / 2.0);
    }
}

void Square::draw(sf::RenderTarget& target) const {
    target.draw(shape);
    if (piece.has_value()) {
        target.draw(*piece.value() );
    }
}


// unused
void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

// Piece* Square::getPiece() {
//     if (this->occupied == false) {
//         throw UnoccupiedSquare();
//     } else {
//         return this->piece;
//     }
// }