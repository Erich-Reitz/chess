#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"
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

  std::optional<ValidPosition> getRowAndColOfMouse(const sf::Vector2f mousePos) const;
  Square *squareAt(const ValidPosition &coord) const;
  Square *squareAt(int row, int col) const ;

 private:
  std::unordered_map<std::string, sf::Texture *> m_textures ;
  std::vector<std::vector<Square *>> board = std::vector<std::vector<Square *>> (8, std::vector<Square *>(8));
};
