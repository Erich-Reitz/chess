#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "Piece.hpp"

Piece::Piece() {
    std::cout << "piece init called" << std::endl;
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

void Piece::draw(sf::RenderTarget &window) const {};

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(piece);
}



