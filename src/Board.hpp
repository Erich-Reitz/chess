#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"
#include "Move.hpp"
#include "ValidPosition.hpp"

class Piece;
class Square;

class Board : public sf::Drawable {
  public:
    Board();
    Board(const Board& rhs);
    Board& operator=(const Board& rhs);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::optional<Piece*> pieceAtPosition(const ValidPosition& pos) const;
    bool hasPieceAtPosition(const ValidPosition& pos) const ;
    void movePiece(const ValidPosition &currentPosition, const ValidPosition &destination) ;
    void removeAndSetPiece(Piece* piece, const ValidPosition &currentPosition, const ValidPosition &destination) ;
    void setSquareColor(const ValidPosition& position, sf::Color color) ;
    std::optional<ValidPosition> getRowAndColOfMouse(sf::Vector2f mousePos) const;
    std::vector<Move> generateAllValidMovesForPiece(const ValidPosition& current, const Piece *piece, bool careIfPlacesKingInCheck=true) const;
    void resetAllSquaresColor();
    void processMove(const Move &move) ;
    PieceColor getColorToMove() const ;
    bool unmovedRookAtPosition(const ValidPosition &pos) const;
    bool hasPieceAtPosition(const ValidPosition &pos, PieceColor targetColor) const;
    std::vector<Move> moveList;
  protected:
    std::vector<std::vector<Square*>> board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));

    bool king_is_attacked(PieceColor colorKingWeAreConcernedAbout) const;
    bool moves_finishes_with_king_in_check(const Move &move) const ;
    bool legal_move(const Move &move, bool careIfPlacesKingInCheck) const ;

    std::vector<Move> generateAllDiagonalMoves(const ValidPosition& current, PieceColor color) const ;
    std::set<std::pair<ValidPosition, Piece*>> getAllPieces(PieceColor search_color) const ;
    Square *squareAt(const ValidPosition &coord) const;
    Square* squareAt(int row, int col) const ;
    std::pair<ValidPosition, Piece*> getKing(PieceColor color) const ;
    PieceColor colorToMove = PieceColor::WHITE ;
};
