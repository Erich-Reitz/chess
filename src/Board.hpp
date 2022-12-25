#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"
#include "Move.hpp"

class Board : public sf::Drawable {
  public:
    Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    [[nodiscard]] std::optional<Piece*> pieceAtPosition(const Position& pos) const;
    [[nodiscard]] bool hasPieceAtPosition(const Position& pos) const ;


    void move(const Position& current, const Position& destination);

    void setSquareColor(const Position& position, sf::Color color) ;

    [[nodiscard]] std::optional<Position> getRowAndColOfMouse(sf::Vector2f mousePos) const;
    [[nodiscard]] std::set<Move> generateAllValidMovesForPiece(const Position& current, const Piece *piece) const;

    void resetAllSquaresColor();
    void removePieceFromSquare(const Position& coordinates);
  protected:
    std::vector<std::vector<Square*>> board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));

    std::set<Move> generateAllValidMovesForPawn(const Position& current, const Piece *piece) const;

    std::set<Move> generateAllValidMovesForRook(const Position& current, const Piece *piece) const;
    std::set<Move> generateAllValidMovesForBishop(const Position& current, const Piece *piece) const;


    [[nodiscard]] bool hasPieceAtPosition(const Position &pos, bool targetColorIsWhite) const;

    [[nodiscard]] bool hasPieceAtPosition(size_t row, size_t col, bool targetColorIsWhite) const;
    [[nodiscard]] std::set<Move> generateValidMovesUpLeftDiagonal(const Position& current, bool pieceIsWhite) const ;

    [[nodiscard]] std::set<Move> generateValidMovesUpRightDiagonal(const Position &current, bool pieceIsWhite) const;

    [[nodiscard]] std::set<Move> generateValidMovesDownRightDiagonal(const Position &current, bool pieceIsWhite) const;

    [[nodiscard]] std::set<Move> generateValidMovesDownLeftDiagonal(const Position &current, bool pieceIsWhite) const;

    [[nodiscard]] Square *squareAt(const Position &coord) const;
};
