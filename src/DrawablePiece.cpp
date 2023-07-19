#include <SFML/Graphics.hpp>

#include <set>

#include "Board.hpp"
#include "DrawablePiece.hpp"
#include "chess_exceptions.hpp"
#include "move_generation.hpp"




DrawablePiece::~DrawablePiece() = default;;

DrawablePiece::DrawablePiece(bool _white, PieceType _type, float squareXPos, float squareYPos,
                             sf::Texture *texture  ) : GameObject(squareXPos, squareYPos,
                                   .0625, texture)  {
  if (_white) {
    this->color = PieceColor::WHITE;
  } else {
    this->color = PieceColor::BLACK;
  }
  this->type = _type;
  std::string piece_color_string;
  if (_white) {
    piece_color_string = "w";
  } else {
    piece_color_string = "b";
  }
  std::string piece_name_string ;
  switch (_type) {
  case PieceType::ROOK:
    piece_name_string = "rook";
    break;
  case PieceType::BISHOP:
    piece_name_string = "bishop";
    break;
  case PieceType::QUEEN:
    piece_name_string = "queen";
    break;
  case PieceType::KING:
    piece_name_string = "king";
    break;
  case PieceType::KNIGHT:
    piece_name_string = "knight";
    break;
  case PieceType::PAWN:
    piece_name_string = "pawn";
    break;
  default:
    throw PieceTypeSwitchFallthrough();
  }
  this->timesMoved = 0;
  const std::string texture_path = "assets/textures/pieces/no_shadow/2x/" + piece_color_string + "_" + piece_name_string  +"_2x_ns.png";
}

DrawablePiece::DrawablePiece(const DrawablePiece &rhs) : GameObject(rhs), timesMoved(rhs.timesMoved), color(rhs.color), type(rhs.type) {
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


bool DrawablePiece::hasMoved() const {
  return this->timesMoved != 0;
}





