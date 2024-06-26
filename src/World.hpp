#pragma once
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Board.hpp"
#include "SelectedPieceInfo.hpp"

#include "PawnPromotionDialog.hpp"

enum WORLD_STATE {
  BOARD,
  PAWN_PROMOTION_DIALOG
} ;

class World  {

 public:
  World() = default;
  World(std::unordered_map<std::string, sf::Texture *> l_textures);
  ~World();

  void update(sf::Time deltaTime);
  void Render(sf::RenderWindow &l_window);

  void HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp);

 private:
  void handleMouseDownOnBoardWithSelectedPiece(const ValidPosition &pressedSquare);
  void handleMouseDownOnBoardWithNoSelectedPiece(const ValidPosition &pressedSquare);
  void handleMouseDown(sf::Vector2f mousePos);
  void handleMouseDownOnBoard(sf::Vector2f mousePos) ;

  void handleMouseDownOnSquare(const ValidPosition &pressedCoordinates);
  void handleMouseDownOnPawnPromotionDialog(sf::Vector2f mousePos) ;
  void displayPawnPromotionDialog();


  // updates
  std::unordered_map<std::string, sf::Texture *> m_textures;
  Board gameBoard;
  sf::Vector2f m_viewCenter;
  sf::Vector2f m_viewSize;
  SelectedPieceInformation selectedPieceInformation;
  PawnPromotionDialog pawnPromotionDialog;
  WORLD_STATE worldState = BOARD;
  int debug = 1;

  void moveSelectedPiece(const ValidPosition &destination);

  void handleUserReselectingPiece(const ValidPosition &pressedSquare);

  void clearSelectedPieceInformation();
};