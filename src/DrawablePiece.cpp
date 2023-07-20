#include <SFML/Graphics.hpp>

#include <set>

#include "Board.hpp"
#include "DrawablePiece.hpp"
#include "chess_exceptions.hpp"
#include "move_generation.hpp"




DrawablePiece::~DrawablePiece() = default;;


DrawablePiece::DrawablePiece(PieceColor pieceColor, PieceType type, float squareXPos, float squareYPos,
                             sf::Texture *texture  ) : GameObject(squareXPos, squareYPos,
                                   .0625, texture), Piece(pieceColor, type) {
}

DrawablePiece::DrawablePiece(const DrawablePiece &rhs) : GameObject(rhs), Piece(rhs) {
}


DrawablePiece &DrawablePiece::operator=(const DrawablePiece &rhs) {
  if (this != &rhs) {
    color = rhs.color;
    type = rhs.type;
    timesMoved = rhs.timesMoved;
  }
  return *this;
}


void DrawablePiece::setPosition(float x, float y) {
  sprite.setPosition(x, y);
  sprite.setOrigin(sprite.getLocalBounds().width/ 2, sprite.getLocalBounds().height/ 2);
}

void DrawablePiece::setRadius(float radius) {
  if (this->type == PieceType::PAWN) {
    sprite.setScale(.065, .065);
  } else {
    sprite.setScale(.06, .06);
  }
}


void DrawablePiece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite);
}






