#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"
#include "Move.hpp"

class Piece;
class Square;

class Board : public sf::Drawable {
  public:
    Board();
    Board(const Board& rhs);
    Board& operator=(const Board& rhs);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::optional<Piece*> pieceAtPosition(const Position& pos) const;
    bool hasPieceAtPosition(const Position& pos) const ;
    void move(const Position& current, const Position& destination);
    void setSquareColor(const Position& position, sf::Color color) ;
    std::optional<Position> getRowAndColOfMouse(sf::Vector2f mousePos) const;
    std::set<Move> generateAllValidMovesForPiece(const Position& current, const Piece *piece, bool careIfPlacesKingInCheck=true) const;
    void resetAllSquaresColor();
    void processMove(const Move &move) ;
    std::set<Move> generateAllValidMovesForRook(const Position& current, const Piece *piece) const;
    std::set<Move> generateAllValidMovesForBishop(const Position& current, const Piece *piece) const;
    std::set<Move> generateAllValidMovesForQueen(const Position& current, const Piece *piece) const;
    std::set<Move> generateAllValidMovesForKing(const Position& current, const Piece *piece) const ;
    std::set<Move> generateAllValidMovesForKnight(const Position& current, const Piece *piece) const ;
    std::set<Move> generateAllValidMovesForPawn(const Position& current, const Piece *piece) const;
    bool whitetoMove() const ;
  protected:
    std::vector<std::vector<Square*>> board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));
    std::vector<Move> moveList;
    bool king_is_attacked(bool colorKingWeAreConcernedAbout) const;
    std::set<Move> generateMovesInStraightLine(const Position& current, bool pieceIsWhite, const int row_difs[], const int col_difs[]) const;
    bool move_places_king_in_check(const Move &move) const ;
    bool legal_move(const Move &move, bool careIfPlacesKingInCheck) const ;
    bool hasPieceAtPosition(const Position &pos, bool targetColorIsWhite) const;
    std::set<Move> generateAllDiagonalMoves(const Position& current, bool pieceIsWhite) const ;
    std::set<std::pair<Position, Piece*>> getAllPieces(bool coloredWhite) const ;
    Square *squareAt(const Position &coord) const;
    Square* squareAt(int row, int col) const ;
    std::pair<Position, Piece*> getKing(bool white) const ;
    bool whiteToMove = true ;
};
