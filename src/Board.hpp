#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"

class Board : public sf::Drawable {
  public:
    Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    std::optional<Piece*> pieceAtPosition(const Position& pos) const;
    bool hasPieceAtPosition(const Position& pos) const ;

    bool canMove(const Position& current, const Position& destination) const;
    void move(const Position& current, const Position& destination);

    std::optional<Position> getRowAndColOfMouse(sf::Vector2f mousePos) const;
  protected:
    std::vector<std::vector<Square*>> board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));
    void removePieceFromSquare(const Position& coordinates);
    std::set<Position> generateAllValidMovesForPawn(const Position& current, const Piece *piece) const;
    std::set<Position> generateAllValidMovesForPiece(const Position& current, const Piece *piece) const;
    std::set<Position> generateAllValidMovesForRook(const Position& current, const Piece *piece) const;

    bool hasPieceAtPosition(const Position &pos, const bool targetColorIsWhite) const;

    bool hasPieceAtPosition(const size_t row, const size_t col, const bool targetColorIsWhite) const;
};
