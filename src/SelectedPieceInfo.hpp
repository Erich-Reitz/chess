#pragma once

#include <optional>
#include "ValidPosition.hpp"
#include "Move.hpp"
struct SelectedPieceInformation {
    std::optional<ValidPosition> coordinates;
    std::optional<Piece*> piece;
    std::optional<std::vector<Move>> placesCanMove;

    void setCoordinates(const std::optional<ValidPosition>& ValidPosition) {
        this->coordinates = ValidPosition;
    }

    void setPiece(Piece *_piece) {
        this->piece = _piece;
    }

    void setInformation(const std::optional<ValidPosition>& _coordinates, Piece *_piece, const std::vector<Move>& validMoves) {
        this->setCoordinates(_coordinates) ;
        this->setPiece(_piece);
        this->placesCanMove = validMoves;
    }

    [[nodiscard]] std::vector<Move> getPlacesCanMove() const {
        return this->placesCanMove.value();
    }

    [[nodiscard]] ValidPosition getCoordinates() const {
        return coordinates.value();
    }


    [[nodiscard]] Piece *getPiece()  {
        return piece.value();
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