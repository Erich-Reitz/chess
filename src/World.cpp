#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "World.hpp"
#include "Board.hpp"
#include <cassert>

#include "chess_exceptions.hpp"

World::World(std::unordered_map<std::string, sf::Texture *> l_textures) {
  this->m_textures = l_textures;
  this->gameBoard = Board(this->m_textures);
}

World::~World() = default;

std::optional<Move> setOfMovesContainsDestination(const std::vector<Move>  &moveSet, const ValidPosition &destination) {
  for (const auto &move : moveSet) {
    if (move.getDestination() == destination) {
      return move;
    }
  }
  return {};
}

void World::displayPawnPromotionDialog() {
  this->pawnPromotionDialog.setPosition(this->m_viewCenter) ;
  this->worldState = WORLD_STATE::PAWN_PROMOTION_DIALOG;
}

void handleMouseDownOnPawnPromotionDialog(sf::Vector2f mousePos)  {
}

void World::moveSelectedPiece(const ValidPosition &destination) {
  auto validMoves = this->selectedPieceInformation.placesCanMove.value();
  auto validMove = setOfMovesContainsDestination(validMoves, destination) ;
  if (!validMove.has_value()) {
    // the move that the user requested is invalid
    // leave the selected piece, and wait for another input
    return;
  }
  auto move_req = validMove.value();
  if (move_req.move_type == MoveType::PAWN_PROMOTION) {
    // display pawn promotion dialog
    this->displayPawnPromotionDialog();
  }
  try {
    gameBoard.processMove(move_req) ;
  } catch (CurrentSquareDoesNotContainPiece &e) {
    std::cerr << e.what() << std::endl;
  }
  this->clearSelectedPieceInformation();
}

void World::clearSelectedPieceInformation() {
  this->selectedPieceInformation.reset();
}

void World::handleUserReselectingPiece(const ValidPosition &pressedSquare) {
  this->clearSelectedPieceInformation();
  handleMouseDownOnBoardWithNoSelectedPiece(pressedSquare) ;
}



bool sameColor(const Piece *a, const Piece *b) {
  return a->color == b->color;
}

void World::handleMouseDownOnBoardWithSelectedPiece(const ValidPosition &pressedSquare) {
  assert(this->selectedPieceInformation.piece.has_value()) ;
  Piece  *previouslySelectedPiece = this->selectedPieceInformation.piece.value() ;
  std::optional<Piece *> pieceAtValidPosition = gameBoard.pieceAtPosition(pressedSquare) ;
  if (pieceAtValidPosition.has_value() && sameColor(pieceAtValidPosition.value(), previouslySelectedPiece) ) {
    handleUserReselectingPiece(pressedSquare);
    return;
  }
  moveSelectedPiece(pressedSquare);
}


void World::handleMouseDownOnBoardWithNoSelectedPiece(const ValidPosition &pressedSquare) {
  std::optional<Piece *>  piece = gameBoard.pieceAtPosition(pressedSquare) ;
  if (!piece.has_value()) {
    return;
  }
  if (piece.value()->color == this->gameBoard.colorToMove) {
    auto placesCanMove = gameBoard.generateAllValidMovesForPieceAtPosition(pressedSquare);
    this->selectedPieceInformation.setInformation(pressedSquare, piece.value(), placesCanMove);
  }
}

void World::handleMouseDownOnSquare(const ValidPosition &pressedSquare) {
  if (this->selectedPieceInformation.hasSelectedPiece()) {
    return handleMouseDownOnBoardWithSelectedPiece(pressedSquare);
  }
  return handleMouseDownOnBoardWithNoSelectedPiece(pressedSquare);
}

void World::handleMouseDownOnBoard(sf::Vector2f mousePos) {
  std::optional<ValidPosition> pressedValidPosition  = gameBoard.getRowAndColOfMouse(mousePos);
  if (!pressedValidPosition.has_value()) {
    return;
  }
  handleMouseDownOnSquare(pressedValidPosition.value());
}

void World::handleMouseDown(sf::Vector2f mousePos) {
  switch(this->worldState) {
  case WORLD_STATE::BOARD:
    this->handleMouseDownOnBoard(mousePos) ;
    break;
  case WORLD_STATE::PAWN_PROMOTION_DIALOG:
    // this->handleMouseDownOnPawnPromotionDialog(mousePos) ;
    break;
  default:
    throw RuntimeError() ;
  }
}

void World::HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp) {
  if (mouseDown) {
    handleMouseDown(mousePos) ;
  }
}


void World::Render(sf::RenderWindow &window) {
  this->m_viewCenter = window.getView().getCenter();
  this->m_viewSize = window.getView().getSize() ;
  window.draw(gameBoard);
  if (this->worldState == WORLD_STATE::PAWN_PROMOTION_DIALOG) {
    window.draw(this->pawnPromotionDialog) ;
  }
}

void World::update(sf::Time deltaTime) {
}


