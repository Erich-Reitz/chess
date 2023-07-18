#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "DrawableSquare.hpp"
#include "ValidPosition.hpp"
#include "PieceType.hpp"


class BoardStructure : public sf::Drawable {
 public:
  BoardStructure() = default;
  BoardStructure(std::unordered_map<std::string, sf::Texture *> l_textures);
  BoardStructure(const BoardStructure &rhs);
  BoardStructure &operator=(const BoardStructure &rhs);

  void draw(sf::RenderTarget &window) const ;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void movePiece(const ValidPosition &currentPosition, const ValidPosition &destination) ;

  std::optional<ValidPosition> getRowAndColOfMouse(const sf::Vector2f mousePos) const;

  std::optional<DrawablePiece *> pieceAtPosition(const ValidPosition &pos) const;
  DrawableSquare *squareAt(const ValidPosition &coord) const;

  bool unmovedRookAtPosition(const ValidPosition &pos) const;
  ValidPosition getKing(PieceColor color) const ;

 private:
  std::unordered_map<std::string, sf::Texture *> m_textures ;
  std::vector<std::vector<std::unique_ptr<DrawableSquare>>> board; 
  DrawableSquare *squareAt(int i, int j) const;
};
