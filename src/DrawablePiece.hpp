#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "PieceType.hpp"
#include "GameObject.hpp"
#include "Piece.hpp"


class DrawablePiece : public GameObject, public Piece {
 public:
  DrawablePiece(PieceColor pieceColor, PieceType _type, float squareXPos, float squareYPos, sf::Texture *texture) ;
  DrawablePiece(const DrawablePiece &rhs) ;
  DrawablePiece &operator=(const DrawablePiece &rhs);
  ~DrawablePiece() override;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void setPosition(float x, float y);
  void setRadius(float radius);

 private:
};
