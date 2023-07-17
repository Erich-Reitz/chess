#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <set>

#include "Square.hpp"
#include "Move.hpp"
#include "ValidPosition.hpp"
#include "BoardStructure.hpp"
#include "Piece.hpp"


class Board : public sf::Drawable {
  public:
    Board() = default; 
    Board(std::unordered_map<std::string, sf::Texture*> l_textures);
    Board(const Board& rhs);
    Board& operator=(const Board& rhs);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void processMove(const Move &move) ;

    void movePiece(const ValidPosition &currentPosition, const ValidPosition &destination) ;
    void setSquareColor(const ValidPosition& position, sf::Color color) ;
    void resetAllSquaresColor();


    std::optional<Piece*> pieceAtPosition(const ValidPosition& pos) const;
    bool hasPieceAtPosition(const ValidPosition& pos) const ;
    std::vector<Move> generateAllValidMovesForPiece(const ValidPosition& current, bool careIfPlacesKingInCheck=true) const;
    std::optional<ValidPosition> getRowAndColOfMouse(sf::Vector2f mousePos) const;
    bool unmovedRookAtPosition(const ValidPosition &pos) const;
    bool hasPieceAtPosition(const ValidPosition &pos, PieceColor targetColor) const;

    std::vector<Move> moveList;
    PieceColor colorToMove = PieceColor::WHITE ;

  protected:
    BoardStructure board;
    bool king_is_attacked(PieceColor colorKingWeAreConcernedAbout) const;
    bool legal_move(const Move &move, bool careIfPlacesKingInCheck) const ;

    std::vector<Move> generateAllDiagonalMoves(const ValidPosition& current, PieceColor color) const ;
    std::set<std::pair<ValidPosition, Piece*>> getAllPieces(PieceColor search_color) const ;
    Square *squareAt(const ValidPosition &coord) const;
    Square* squareAt(int row, int col) const ;
    std::pair<ValidPosition, Piece*> getKing(PieceColor color) const ;

};
