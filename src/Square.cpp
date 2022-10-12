#include <string>
#include <iostream>

#include "Square.hpp"

Square::Square(bool white) {
    this->white = white;
    this->occupied = false;
    shape.setSize(sf::Vector2f(100.f, 100.f));
    if (white) {
        shape.setFillColor(sf::Color::White);
    } else {
        shape.setFillColor(sf::Color::Black);
    }
}

Square::Square(bool white, Piece* piece) {
    this->white = white;
    this->piece = piece;
    this->occupied = true;
}

void Square::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape);
}

// Piece* Square::getPiece() {
//     if (this->occupied == false) {
//         throw UnoccupiedSquare();
//     } else {
//         return this->piece;
//     }
// }