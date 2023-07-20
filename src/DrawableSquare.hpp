#pragma once

#include <functional>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"

#include "DrawablePiece.hpp"
#include "ValidPosition.hpp"

class DrawableSquare : public GameObject {
 public:
  DrawableSquare() = default;
  DrawableSquare(bool white, float xPos, float yPos, float size, std::optional<PieceType> pieceType, std::optional<PieceColor> pieceColor,

                 sf::Texture *m_texture,
                 std::optional<sf::Texture *> piece_texture);
  DrawableSquare(const DrawableSquare &rhs);
  DrawableSquare &operator=(const DrawableSquare &rhs);
  ~DrawableSquare();
  std::optional<DrawablePiece *> piece() const;


  void setPiece(DrawablePiece *piece);
  void removePiece();

  void draw(sf::RenderTarget &window) const ;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


  void setPieceSize();

 protected:
  bool white;
 private:
  std::optional<DrawablePiece *> m_piece;
  std::unordered_map<std::string, sf::Texture *> m_textures;


};
