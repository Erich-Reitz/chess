#pragma once

#include <optional>
#include "ValidPosition.hpp"
#include "Move.hpp"
struct SelectedPieceInformation {
  std::optional<ValidPosition> coordinates;
  std::optional<DrawablePiece *> piece;
  std::optional<std::vector<Move>> placesCanMove;

  void setInformation(const std::optional<ValidPosition> &_coordinates, DrawablePiece *_piece, const std::vector<Move> &validMoves) {
    this->coordinates = _coordinates;
    this->piece = _piece;
    this->placesCanMove = validMoves;
  }

  [[nodiscard]] bool hasSelectedPiece() const {
    return coordinates.has_value();
  };


  void reset() {
    coordinates = {};
    piece = {};
    this->placesCanMove = {};
  }
};