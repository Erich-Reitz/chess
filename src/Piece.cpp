#include <SFML/Graphics.hpp>

#include "Piece.hpp"


Piece::~Piece() = default;;

Piece::Piece(bool _white, PieceType _type)  {
    this->white = _white;
    this->type = _type;
    if (_white) {
        piece.setFillColor(sf::Color::White);
    } else {
        piece.setFillColor(sf::Color::Black);
    }
}


void Piece::setPosition(float x, float y) {
    piece.setPosition(x, y);
}

void Piece::setRadius(float radius) {
    piece.setRadius(radius);
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(piece);
}

bool Piece::isWhite() const {
    return this->white;
}

bool Piece::isBlack() const {
    return !this->white;
}

bool Piece::hasMoved() const {
    return this->has_self_moved;
}

void Piece::setColor(sf::Color color) {
    this->piece.setFillColor(color);
}

void Piece::setMoved(bool hasMoved) {
    this->has_self_moved = hasMoved;
}

PieceType Piece::getType() const {
    return this->type;
}

void Piece::setOriginalColor() {
    if (isWhite()) {
        setColor(sf::Color::White);
    } else {
        setColor(sf::Color::Black);
    }
}


