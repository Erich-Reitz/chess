#pragma once

#include <optional>
#include "Position.hpp"
#include "Move.hpp"
struct SelectedPieceInformation {
    std::optional<Position> coordinates;
    std::optional<Piece*> piece;
    std::optional<std::set<Move>> placesCanMove;

    void setCoordinates(const std::optional<Position>& position) {
        this->coordinates = position;
    }

    void setPiece(Piece *_piece) {
        this->piece = _piece;
    }

    void setInformation(const std::optional<Position>& _coordinates, Piece *_piece, const std::set<Move>& validMoves) {
        this->setCoordinates(_coordinates) ;
        this->setPiece(_piece);
        this->placesCanMove = validMoves;
    }

    [[nodiscard]] std::set<Move> getPlacesCanMove() const {
        return this->placesCanMove.value();
    }

    [[nodiscard]] Position getCoordinates() const {
        return coordinates.value();
    }


    Piece *getPiece()  {
        return piece.value();
    }

    [[nodiscard]] bool hasSelectedPiece() const {
        return coordinates.has_value();
    };


    void zeroCoordinates() {
        coordinates = {};
    }

    void zeroPiece() {
        piece.value()->setOriginalColor();
        piece = {};
    }
    void reset() {
        zeroCoordinates();
        zeroPiece();
        this->placesCanMove = {};
    }
};