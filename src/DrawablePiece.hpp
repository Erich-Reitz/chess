#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

#include "PieceType.hpp"
#include "Move.hpp"
#include "GameObject.hpp"


class DrawablePiece : public GameObject {
 public:
  DrawablePiece(bool _white, PieceType _type, float squareXPos, float squareYPos, sf::Texture *texture) ;
  DrawablePiece(const DrawablePiece &rhs) ;
  DrawablePiece &operator=(const DrawablePiece &rhs);
  ~DrawablePiece() override;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void setPosition(float x, float y);
  void setRadius(float radius);


  bool hasMoved() const;
  size_t timesMoved;
  PieceType type;
  PieceColor color;
 private:
};
