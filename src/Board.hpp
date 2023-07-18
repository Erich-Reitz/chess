#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "DrawableSquare.hpp"
#include "Move.hpp"
#include "ValidPosition.hpp"
#include "BoardStructure.hpp"
#include "BoardState.hpp"
#include "DrawablePiece.hpp"


class Board : public sf::Drawable {
 public:
  Board() = default;
  Board(std::unordered_map<std::string, sf::Texture *> l_textures);
  Board(const Board &rhs);
  Board &operator=(const Board &rhs);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void processMove(const Move &move) ;

  std::optional<DrawablePiece *> pieceAtPosition(const ValidPosition &pos) const;
  bool hasPieceAtPosition(const ValidPosition &pos) const ;
  std::vector<Move> generateAllValidMovesForPieceAtPosition(const ValidPosition &current, bool careIfPlacesKingInCheck=true) const;
  std::optional<ValidPosition> getRowAndColOfMouse(sf::Vector2f mousePos) const;
  bool unmovedRookAtPosition(const ValidPosition &pos) const;
  bool hasPieceAtPosition(const ValidPosition &pos, PieceColor targetColor) const;
  std::vector<Move> getMoveList() const;
  PieceColor getColorToMove() const;



 protected:
  BoardStructure mBoard;
  BoardState mBoardState;
  bool king_is_attacked(PieceColor colorKingWeAreConcernedAbout) const;
  bool legal_move(const Move &move, bool careIfPlacesKingInCheck) const ;
  DrawableSquare *squareAt(const ValidPosition &coord) const;
  DrawableSquare *squareAt(int row, int col) const ;


};
