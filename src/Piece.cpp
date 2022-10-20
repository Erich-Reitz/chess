#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "Piece.hpp"


Piece::~Piece() {};

Piece::Piece(bool _white)  {
    piece = sf::CircleShape() ;
    this->white = _white;
    if (_white) {
        piece.setFillColor(sf::Color::White);
    } else {
        piece.setFillColor(sf::Color::Black);
    }
}

Piece::Piece() {
    piece = sf::CircleShape() ;
    piece.setFillColor(sf::Color::Green);
};

void Piece::setXPos(float x) {
    float currentY = piece.getPosition().y ;
    piece.setPosition(x, currentY);
}
void Piece::setYPos(float y) {
    float currentX = piece.getPosition().x ;
    piece.setPosition(currentX, y);
}

void Piece::setPosition(float x, float y) {
    piece.setPosition(x, y);
}

void Piece::setRadius(float radius) {
    piece.setRadius(radius);
}

void Piece::draw(sf::RenderTarget &target) const {
    target.draw(piece);
};

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


